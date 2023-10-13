/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:56:42 by ilona             #+#    #+#             */
/*   Updated: 2023/10/13 14:10:08 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_close_pipe(t_info *info, int i)
{
	while (i < info->nb_de_pipe)
	{
		if (close(info->pipe_fd[i][0]) < 0 || close(info->pipe_fd[i][1]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_premier(t_struct *repo, t_info *info)
{
	if (dup2(info->pipe_fd[repo->nb_cmd][1], STDOUT_FILENO) < 0)
		return (1);
	if (ft_close_pipe(info, repo->nb_cmd))
		return (1);
	return (0);
}

int	ft_milieu(t_struct *repo, t_info *info)
{
	if (dup2(info->pipe_fd[repo->nb_cmd - 1][0], STDIN_FILENO) < 0)
		return (1);
	if (dup2(info->pipe_fd[repo->nb_cmd][1], STDOUT_FILENO) < 0)
		return (1);
	if (close(info->pipe_fd[repo->nb_cmd - 1][0]) < 0
		|| close(info->pipe_fd[repo->nb_cmd - 1][1]) < 0)
		return (1);
	if (ft_close_pipe(info, repo->nb_cmd))
		return (1);
	return (0);
}

int	ft_dernier(t_struct *repo, t_info *info)
{
	if (dup2(info->pipe_fd[repo->nb_cmd - 1][0], STDIN_FILENO) < 0)
		return (1);
	if (close(info->pipe_fd[repo->nb_cmd - 1][0]) < 0
		|| close(info->pipe_fd[repo->nb_cmd - 1][1]) < 0)
		return (1);
	if (dup2(info->saved_stdout, STDOUT_FILENO) < 0)
		return (1);
	return (0);
}

int	ft_pipe(t_struct *repo, t_info *info)
{
	if (repo->nb_cmd == 0)
		return (ft_premier(repo, info));
	else if (repo->nb_cmd > 0 && info->nb_de_pipe > repo->nb_cmd)
		return (ft_milieu(repo, info));
	else
		return (ft_dernier(repo, info));
	return (0);
}
