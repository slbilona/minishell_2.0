/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/10/11 19:25:16 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*ft_cherche_path_suite(t_struct *repo, t_info *info, int *i)
{
	char	*path_entier;

	if ((repo->cmd && ft_strlen(repo->cmd) == 0)
		|| ft_directory_ou_non(repo->cmd))
		return (NULL);
	if (access(repo->cmd, X_OK) == 0)
		return (ft_strdup(repo->cmd));
	while (info->env && info->env[*i])
	{
		path_entier = ft_strnstr(info->env[*i], "PATH=", 5);
		if (path_entier)
			break ;
		*i += 1;
	}
	return (path_entier);
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
	path_entier = ft_cherche_path_suite(repo, info, &i);
	if (!path_entier)
		return (NULL);
	splited_path = ft_new_split(info->env[i] + 5, ":");
	if (!splited_path)
		return (NULL);
	i = -1;
	while (splited_path && splited_path[++i])
	{
		path = ft_strjoin(splited_path[i], "/");
		path_cmd = ft_strjoin(path, repo->cmd);
		free(path);
		if (access(path_cmd, X_OK) == 0)
			return (ft_free_double_string(splited_path), path_cmd);
		free(path_cmd);
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
	}
}

void	ft_post_exec(t_struct *repo, t_info *info)
{
	if (info->fork)
		ft_wait(info);
	if (info->i_heredoc)
		unlink("/tmp/heredoc.txt");
	free(info->diff_pid);
	info->i_diff_pid = 0;
	ft_free_pipe(info);
	dup2(info->saved_stdout, STDOUT_FILENO);
	dup2(info->saved_stdin, STDIN_FILENO);
	ft_free_struct(repo, info, 0);
}

int	ft_execution_coordinateur(t_struct *repo, t_info *info)
{
	info->i = 0;
	if (info->nb_de_pipe > 0)
	{
		info->pipe_fd = ft_init_pipe(info);
		if (ft_verif_pipe_fd(info, repo))
			return (1);
	}
	else
		info->pipe_fd = NULL;
	while (info->i < info->nb_de_cmd)
	{
		if (ft_heredoc(info, repo))
			return (1);
		if (info->nb_de_pipe != 0 || ft_builtins_ou_non(&repo[info->i], info))
		{
			if (ft_fork(repo, info))
				break ;
		}
		else
			info->exit = ft_builtins(repo, info);
		info->i++;
	}
	ft_post_exec(repo, info);
	return (0);
}
