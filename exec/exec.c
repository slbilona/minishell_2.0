/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/09/14 14:25:59 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    ft_redirection(char **str)
{
	int i;
	int fd;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp("> ", str[i], 2) == 0)
		{
			fd = open(str[i] + 2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("Erreur lors de la redirection de la sortie standard");
				return ;
			}
		}
		else
			printf("ilona\n");
		i++;
	}
	close(fd);
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
	info->path = ft_cherche_path(repo, info);
	if (!info->path)
		return ;
	//printf("repo->args[0] : %s\n", repo->args[0]);
	if (execve(info->path, repo->args, info->env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	ft_builtins_ou_non(t_struct *repo, t_info *info)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (strncmp(repo->cmd, info->builtins[i].str, strlen(info->builtins[i].str)) == 0)
		{
			if (repo[i].redirection)
				ft_redirection(repo[i].redirection);
			else //pas obligatoire
				dup2(STDOUT_FILENO, STDOUT_FILENO);
			info->builtins[i].ptr(repo, info);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_fork(t_struct *repo, t_info *info, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (repo[i].redirection)
			ft_redirection(repo[i].redirection);
		else //pas obligatoire
			dup2(STDOUT_FILENO, STDOUT_FILENO);
		//regarder si la commande fait partie des builtins ou non
		ft_execve(&repo[i], info);
	}
	return (0);
}

int	ft_execution(t_struct *repo, t_info *info)
{
	int i;

	i = 0;
	while (i < info->nb_de_cmd)
	{
		if(ft_builtins_ou_non(&repo[i], info))
			ft_fork(repo, info, i);
		i++;
	}
	wait(NULL);
	ft_free_struct(repo, info, 0);//free la structure repo
	return (0);
}
