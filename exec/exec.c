/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/10/09 16:13:42 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

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
	if ((repo->cmd && ft_strlen(repo->cmd) == 0))
		return (NULL);
	if (ft_directory_ou_non(repo->cmd))
		return (NULL);
	if (access(repo->cmd, X_OK) == 0)
		return (ft_strdup(repo->cmd));
	while (info->env && info->env[i])
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
	while (splited_path && splited_path[i])
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
		perror("Minishell: execve:");
		repo->ret = 1;
		//exit(EXIT_FAILURE);
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
					redir = ft_redirection(repo->redirection);
				if (!redir)
					repo->ret = info->builtins[i].ptr(repo, info);
				else
					repo->ret = redir;
				return (repo->ret);
			}
		}
		i++;
	}
	return (1);
}

void ft_erreur_path(t_info *info, t_struct *repo, int **pipe_fd)
{
	int i;

	i = info->i;
	info->fork = 0;
	if (ft_directory_ou_non(repo[i].cmd))
		ft_put_str_error("Minishell: ", repo[i].cmd,
			" : est un dossier", NULL);
	else
		ft_put_str_error("Minishell: ", repo[i].cmd,
			" : commande introuvable", NULL);
	if (repo[i].nb_cmd > 0 && info->nb_de_pipe > 0)
	{
		close(pipe_fd[repo[i].nb_cmd - 1][0]);
		close(pipe_fd[repo[i].nb_cmd - 1][1]);
	}
	if (info->nb_de_pipe > repo[i].nb_cmd && info->nb_de_pipe > 0)
	{
		close(pipe_fd[repo[i].nb_cmd][0]);
		close(pipe_fd[repo[i].nb_cmd][1]);
	}
	ft_free_pipe(info, pipe_fd);
	ft_free_struct(repo, info, 2); //free les structures
	exit(127);
}

void	ft_processus_fils(t_info *info, t_struct *repo, int redir, int **pipe_fd)
{
	int i;
	int ex;

	i = info->i;
	if (repo[i].cmd && ft_builtins_ou_non(&repo[i], info, 1))
	{
		repo[i].path = ft_cherche_path(&repo[i], info);
		if (!repo[i].path)
			ft_erreur_path(info, repo, pipe_fd);
	}
	if (repo[i].nb_cmd > 0 && info->nb_de_pipe > 0)
	{
		dup2(pipe_fd[repo[i].nb_cmd - 1][0], STDIN_FILENO); // Redirection de l'entrée standard depuis le tube précédent
		close(pipe_fd[repo[i].nb_cmd - 1][0]);
		close(pipe_fd[repo[i].nb_cmd - 1][1]);
	}
	if (info->nb_de_pipe > repo[i].nb_cmd && info->nb_de_pipe > 0)
	{
		dup2(pipe_fd[repo[i].nb_cmd][1], STDOUT_FILENO);
		close(pipe_fd[repo[i].nb_cmd][0]);
		close(pipe_fd[repo[i].nb_cmd][1]);
	}
	if (repo[i].redirection)
		redir = ft_redirection(repo[i].redirection);
	if (repo[i].cmd && !redir && ft_builtins_ou_non(&repo[i], info, 0))
	{
		ft_execve(&repo[i], info);
	}
	if (redir)
		ex = redir;
	else
		ex = repo[i].ret;
	ft_free_pipe(info, pipe_fd);
	ft_free_struct(repo, info, 2); //free les structures
	exit(ex);
}

int	ft_fork(t_struct *repo, t_info *info, int **pipe_fd)
{
	int		i;
	int		redir;

	i = info->i;
	redir = 0;
	info->fork = 1;
	info->diff_pid[repo[i].nb_cmd] = fork();
	if (info->diff_pid[repo[i].nb_cmd] == -1)
	{
		perror("Minishell: fork");
		info->fork = 0;
		info->exit = 1;
		return (1);
	}
	else if (info->diff_pid[repo[i].nb_cmd] == 0)
		ft_processus_fils(info, repo, redir, pipe_fd);
	else
	{
		if (info->nb_de_pipe && repo[i].nb_cmd > 0)
		{
			close(pipe_fd[repo[i].nb_cmd - 1][0]);
			close(pipe_fd[repo[i].nb_cmd - 1][1]);
		}
	}
	return (0);
}

void	ft_wait(t_info *info)
{
	int	i;
	int	status;
	int	exit_signal;

	i = 0;
	while (i < info->nb_de_cmd && info->diff_pid[i])
	{
		waitpid(info->diff_pid[i++], &status, 0);
		if (WIFEXITED(status))
			info->exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			exit_signal = WTERMSIG(status);
			if (exit_signal == SIGINT)
				info->exit = 130;
			else if (exit_signal == SIGQUIT)
				info->exit = 131;
		}
	}
}

int	ft_execution_coordinateur(t_struct *repo, t_info *info)
{
	int		**pipe_fd;

	info->i = 0;
	if (info->nb_de_pipe > 0)
	{
		pipe_fd = ft_init_pipe(info);
		if (!pipe_fd)
		{
			ft_put_str_error("Minishell: ", "pipe: erreur",
				" lors de", " l'allocation");
			free(info->diff_pid);
			// dup2(info->saved_stdout, STDOUT_FILENO);
			// dup2(info->saved_stdin, STDIN_FILENO);
			ft_free_struct(repo, info, 0);//free la structure repo
			info->exit = 1;
			return (1);
		}
	}
	else
		pipe_fd = NULL;
	while (info->i < info->nb_de_cmd)
	{
		if (ft_heredoc_ou_non(repo[info->i].redirection))
		{
			if (ft_heredoc(info, repo[info->i].redirection))
			{
				free(info->diff_pid);
				ft_free_pipe(info, pipe_fd);
				// dup2(info->saved_stdout, STDOUT_FILENO);
				// dup2(info->saved_stdin, STDIN_FILENO);
				ft_free_struct(repo, info, 0);//free la structure repo
				return (1);
			}
		}
		if (info->nb_de_pipe != 0 || ft_builtins_ou_non(&repo[info->i], info, 1))
		{
			if (ft_fork(repo, info, pipe_fd))
				break;
		}
		else
			info->exit = ft_builtins_ou_non(&repo[info->i], info, 0);

		info->i++;
	}
	if (info->fork)
		ft_wait(info);
	if (info->i_heredoc)
		unlink("/tmp/heredoc.txt");
	free(info->diff_pid);
	ft_free_pipe(info, pipe_fd);
	//dup2(info->saved_stdout, STDOUT_FILENO);
	//dup2(info->saved_stdin, STDIN_FILENO);
	ft_free_struct(repo, info, 0);//free la structure repo
	return (0);
}
