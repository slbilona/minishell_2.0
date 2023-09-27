/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/09/27 18:00:42 by ilselbon         ###   ########.fr       */
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
				ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
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
				ft_put_str_error("Minishell: ", str[i] + 3, ": ", strerror(errno));
				return (1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				ft_put_str_error("Minishell: ", str[i] + 3, ": ", strerror(errno));
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
				ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
				return (1);
			}
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
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
	if (repo->cmd && ft_strlen(repo->cmd) == 0)
		return (NULL);
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
	splited_path = ft_new_split(info->env[i] + 5, ":");
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

/* Verifie si la commande fait partie des builtins.
Si c'est le cas la fonction associée est appellée */
int	ft_builtins_ou_non(t_struct *repo, t_info *info, int j)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	while (i < 7)
	{
		if (j)
		{
			if (ft_strncmp(repo->cmd, info->builtins[i].str,
					ft_strlen(repo->cmd)) == 0
				&& ft_strncmp(repo->cmd, info->builtins[i].str,
					ft_strlen(info->builtins[i].str)) == 0)
				return (0);
		}
		else
		{
			if (ft_strncmp(repo->cmd, info->builtins[i].str,
					ft_strlen(repo->cmd)) == 0
				&& ft_strncmp(repo->cmd, info->builtins[i].str,
					ft_strlen(info->builtins[i].str)) == 0)
			{
				if (repo->redirection)
					redir = ft_redirection(repo->redirection, repo, info);
				if (!redir)
					info->builtins[i].ptr(repo, info);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	ft_processus_fils(t_info *info, t_struct *repo, int redir, int **pipe_fd)
{
	if (repo->nb_cmd > 0 && info->nb_de_pipe > 0)
	{
		dup2(pipe_fd[repo->nb_cmd - 1][0], STDIN_FILENO); // Redirection de l'entrée standard depuis le tube précédent
		close(pipe_fd[repo->nb_cmd - 1][0]);
		close(pipe_fd[repo->nb_cmd - 1][1]);
	}
	if (info->nb_de_pipe > repo->nb_cmd && info->nb_de_pipe > 0)
	{
		dup2(pipe_fd[repo->nb_cmd][1], STDOUT_FILENO);
		close(pipe_fd[repo->nb_cmd][0]);
		close(pipe_fd[repo->nb_cmd][1]);
	}
	if (repo->redirection)
		redir = ft_redirection(repo->redirection, repo, info);
	if (repo->cmd && !redir && ft_builtins_ou_non(repo, info, 0))
	{
		ft_execve(repo, info);
	}
	exit(0);
}

int	ft_fork(t_struct *repo, t_info *info, int **pipe_fd)
{
	int		redir;

	redir = 0;
	if (ft_builtins_ou_non(repo, info, 1))
	{
		repo->path = ft_cherche_path(repo, info);
		if (!repo->path)
		{
			ft_put_str_error("Minishell: ", repo->cmd,
				" : commande introuvable", NULL);
			return (1);
		}
	}
	info->fork = 1;
	info->diff_pid[repo->nb_cmd] = fork();
	if (info->diff_pid[repo->nb_cmd] == -1)
	{
		perror("fork");
		return (1);
	}
	else if (info->diff_pid[repo->nb_cmd] == 0)
	{
		ft_processus_fils(info, repo, redir, pipe_fd);
	}
	else
	{
		if (info->nb_de_pipe && repo->nb_cmd > 0)
		{
			close(pipe_fd[repo->nb_cmd - 1][0]);
			close(pipe_fd[repo->nb_cmd - 1][1]);
		}
	}
	return (0);
}

/* si j == 0 : initialise pipe_fd
sinn free pipe_fd */
int	**ft_init_free_pipe(t_info *info, int j, int **pipes_fd)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	if (!j)
	{
		pipe_fd = malloc(sizeof(int *) * info->nb_de_pipe);
		while (i < info->nb_de_pipe)
		{
			pipe_fd[i] = malloc(sizeof(int) * 2);
			// Verifier si l'allocation n'a pas echoue
			if (pipe(pipe_fd[i]) == -1)
			{
				perror("Erreur lors de la création des tubes");
				return (NULL);
			}
			i++;
		}
		return (pipe_fd);
	}
	else
	{
		while (i < info->nb_de_pipe)
			free(pipes_fd[i++]);
		free(pipes_fd);
		return (NULL);
	}
	return (NULL);
}

void	ft_wait(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->nb_de_cmd && info->diff_pid[i])
		waitpid(info->diff_pid[i++], &status, 0);
}

int	ft_execution_coordinateur(t_struct *repo, t_info *info)
{
	int		i;
	int		**pipe_fd;

	i = 0;
	if (info->nb_de_pipe > 0)
		pipe_fd = ft_init_free_pipe(info, 0, NULL);
	else
		pipe_fd = NULL;
	while (i < info->nb_de_cmd)
	{
		if (info->nb_de_pipe != 0 || ft_builtins_ou_non(&repo[i], info, 1))
			ft_fork(&repo[i], info, pipe_fd);
		else
			ft_builtins_ou_non(&repo[i], info, 0);
		if (repo[i].i_heredoc)
			unlink("/tmp/heredoc.txt");
		i++;
	}
	if (info->fork)
		ft_wait(info);
	info->fork = 0;
	free(info->diff_pid);
	ft_init_free_pipe(info, 1, pipe_fd);
	dup2(info->saved_stdout, STDOUT_FILENO);
	dup2(info->saved_stdin, STDIN_FILENO);
	ft_free_struct(repo, info, 0);//free la structure repo
	return (0);
}
