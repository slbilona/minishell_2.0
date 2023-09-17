/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/09/17 01:52:49 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_redirection(char **str, t_info *info)
{
	int	i;
	int	fd;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp("> ", str[i], 2) == 0)
		{
			fd = open(str[i] + 2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				printf("minishell: %s: %s\n", str[i] + 2, strerror(errno));
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				printf("minishell: %s: %s\n", str[i] + 2, strerror(errno));
				close(fd);
				return (1);
			}
		}
		else if (ft_strncmp(">> ", str[i], 3) == 0)
		{
			fd = open(str[i] + 3, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				printf("minishell: %s: %s\n", str[i] + 3, strerror(errno));
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				printf("minishell: %s: %s\n", str[i] + 3, strerror(errno));
				close(fd);
				return (1);
			}
		}
		else if (ft_strncmp("< ", str[i], 2) == 0)
		{
			fd = open(str[i] + 2, O_RDONLY, 0644);
			if (fd == -1)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				printf("minishell: %s: %s\n", str[i] + 2, strerror(errno));
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				printf("minishell: %s: %s\n", str[i] + 2, strerror(errno));
				close(fd);
				return (1);
			}
		}
		else
			printf("ilona\n");
		close(fd);
		i++;
	}
	return (0);
}

/*Cherche la ligne "PATH=" dans l'environnement
puis cherche avec access le bon chemin pour la commande envoyé*/
char	*ft_cherche_path(t_struct *repo, t_info *info)
{
	int		i;
	char	*path;
	char	*path_cmd;
	char	*path_entier;
	char	**splited_path;

	i = 0;
	if (access(repo->cmd, F_OK) == 0)
		return (repo->cmd);
	while (info->env[i])
	{
		path_entier = ft_strnstr(info->env[i], "PATH=", 5);
		if (path_entier)
			break ;
		i++;
	}
	if (!path_entier)
		return (NULL);
	splited_path = ft_split(info->env[i] + 5, ':');
	if (!splited_path)
		return (NULL);
	i = 0;
	while (splited_path[i])
	{
		path = ft_strjoin(splited_path[i], "/");
		path_cmd = ft_strjoin(path, repo->cmd);
		free(path);
		if (access(path_cmd, F_OK) == 0)
			return (ft_free_double_string(splited_path), path_cmd);
		free(path_cmd);
		i++;
	}
	ft_free_double_string(splited_path);
	return (NULL);
}

void	ft_execve(t_struct *repo, t_info *info)
{
	//printf("repo->args[0] : %s\n", repo->args[0]);
	if (execve(repo->path, repo->args, info->env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	ft_builtins_ou_non(t_struct *repo, t_info *info)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (strncmp(repo->cmd, info->builtins[i].str,
				strlen(info->builtins[i].str)) == 0)
		{
			if (repo->redirection)
			{
				if (ft_redirection(repo->redirection, info))
					return (0);
			}
			else //pas obligatoire
				dup2(info->saved_stdout, STDOUT_FILENO);
			info->builtins[i].ptr(repo, info);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_fork(t_struct *repo, t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		ft_execve(repo, info);
	}
	return (0);
}

// int	ft_execution(t_struct *repo, t_info *info)
// {
// 	int	i;

// 	i = 0;
// 	while (i < info->nb_de_cmd)
// 	{
// 		if (ft_builtins_ou_non(&repo[i], info))
// 			ft_fork(repo, info, i);
// 		i++;
// 	}
// 	wait(NULL);
// 	ft_free_struct(repo, info, 0);//free la structure repo
// 	return (0);
// }

int	ft_execution_coordinateur(t_struct *repo, t_info *info)
{
	// int i;

	// i = 0;
	// while (i < info->nb_de_cmd)
	// {
	// 	if (!repo[i].cmd && repo[i].redirection)
	// 	{
	// 		ft_redirection(repo[i].redirection);
	// 	}
	// 	else if (ft_builtins_ou_non(&repo[i], info))
	// 	{
	// 			repo[i].path = ft_cherche_path(&repo[i], info);
	// 			//printf("%s\n", repo[i].path);
	// 			if (!repo[i].path)
	// 				printf("minishell: %s : commande introuvable\n", repo[i].cmd);
	// 			else
	// 				ft_fork(&repo[i], info);
	// 	}
	// 	dup2(0, STDIN_FILENO);
	// 	dup2(1, STDOUT_FILENO);
	// 	i++;
	// }
	// wait(NULL);
	// ft_free_struct(repo, info, 0);//free la structure repo
	// return (0);
	
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (i < info->nb_de_cmd)
	{
		if (repo[i].redirection)
			redir = ft_redirection(repo[i].redirection, info);
		if (repo[i].cmd && !redir && ft_builtins_ou_non(&repo[i], info))
		{
			//printf("ceci est untest\n");
			repo[i].path = ft_cherche_path(&repo[i], info);
			if (!repo[i].path)
			{
				dup2(info->saved_stdout, STDOUT_FILENO);
				// trpuver un moyen pour que le message d'erreur soit rediriger dans la bonne sortie
				printf("minishell: %s : commande introuvable\n", repo[i].cmd);
			}
			else
				ft_fork(&repo[i], info);
		}
		dup2(info->saved_stdout, STDOUT_FILENO);
		dup2(info->saved_stdin, STDIN_FILENO);
		i++;
	}
	wait(NULL);
	ft_free_struct(repo, info, 0);//free la structure repo
	return (0);
}
