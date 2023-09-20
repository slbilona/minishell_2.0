/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/09/20 20:37:27 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_redirection(char **str, t_struct *repo, t_info *info)
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
				dup2(info->saved_stderr, STDERR_FILENO);
				printf("Minishell: %s: %s\n", str[i] + 2, strerror(errno));
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				dup2(info->saved_stderr, STDERR_FILENO);
				printf("Minishell: %s: %s\n", str[i] + 2, strerror(errno));
				close(fd);
				return (1);
			}
			close(fd);
		}
		else if (ft_strncmp(">> ", str[i], 3) == 0)
		{
			fd = open(str[i] + 3, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				dup2(info->saved_stderr, STDERR_FILENO);
				printf("Minishell: %s: %s\n", str[i] + 3, strerror(errno));
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				dup2(info->saved_stderr, STDERR_FILENO);
				printf("Minishell: %s: %s\n", str[i] + 3, strerror(errno));
				close(fd);
				return (1);
			}
			close(fd);
		}
		else if (ft_strncmp("< ", str[i], 2) == 0)
		{
			fd = open(str[i] + 2, O_RDONLY, 0644);
			if (fd == -1)
			{
				dup2(info->saved_stderr, STDERR_FILENO);
				printf("Minishell: %s: %s\n", str[i] + 2, strerror(errno));
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				dup2(info->saved_stderr, STDERR_FILENO);
				printf("Minishell: %s: %s\n", str[i] + 2, strerror(errno));
				close(fd);
				return (1);
			}
			close(fd);
		}
		else if (ft_strncmp("<< ", str[i], 3) == 0)
			ft_heredoc(str[i] + 3, repo, info);
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
	if (access(repo->cmd, X_OK) == 0)
		return (ft_strdup(repo->cmd));
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
		if (access(path_cmd, X_OK) == 0)
			return (ft_free_double_string(splited_path), path_cmd);
		free(path_cmd);
		i++;
	}
	ft_free_double_string(splited_path);
	return (NULL);
}

void	ft_execve(t_struct *repo, t_info *info)
{
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
	while (i < 7)
	{
		if (strncmp(repo->cmd, info->builtins[i].str,
				strlen(info->builtins[i].str)) == 0)
		{
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
		// close(repo->pipe_fd[0]);
		// dup2(repo->pipe_fd[1], STDOUT_FILENO);
		ft_execve(repo, info);
	}
	else
	{
		// close(repo->pipe_fd[1]);
		// dup2(repo->pipe_fd[0], STDOUT_FILENO);
	}
	return (0);
}

int	ft_execution_coordinateur(t_struct *repo, t_info *info)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (i < info->nb_de_cmd)
	{
		if (repo[i].redirection)
			redir = ft_redirection(repo[i].redirection, &repo[i], info);
		// if (i < info->nb_de_pipe)
		// {
		// 	if (pipe(repo[i].pipe_fd) == -1)
		// 	{
		// 		perror("pipe");
		// 	}
		// }
		if (repo[i].cmd && !redir && ft_builtins_ou_non(&repo[i], info))
		{
			repo[i].path = ft_cherche_path(&repo[i], info);
			if (!repo[i].path)
			{
				dup2(info->saved_stderr, STDERR_FILENO);
				// trouver un moyen pour que le message d'erreur soit rediriger dans la bonne sortie
				printf("Minishell: %s : commande introuvable\n", repo[i].cmd);
			}
			else
				ft_fork(&repo[i], info);
		}
		if (repo[i].i_heredoc)
			unlink("/tmp/heredoc.txt");
		dup2(info->saved_stdout, STDOUT_FILENO);
		dup2(info->saved_stdin, STDIN_FILENO);
		i++;
	}
	wait(NULL);
	ft_free_struct(repo, info, 0);//free la structure repo
	return (0);
}
