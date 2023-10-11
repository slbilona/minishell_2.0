/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:56:42 by ilona             #+#    #+#             */
/*   Updated: 2023/10/11 18:57:22 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_premier(t_struct *repo, t_info *info)
{
	if (dup2(info->pipe_fd[repo->nb_cmd][1], STDOUT_FILENO) < 0)
		return (1);
	if (close(info->pipe_fd[repo->nb_cmd][0]) < 0
		|| close(info->pipe_fd[repo->nb_cmd][1]) < 0)
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
	if (close(info->pipe_fd[repo->nb_cmd][0]) < 0
		|| close(info->pipe_fd[repo->nb_cmd][1]) < 0)
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
	//verifier
	if (repo->nb_cmd == 0)
		ft_premier(repo, info);
	else if (repo->nb_cmd > 0 && info->nb_de_pipe > repo->nb_cmd)
		ft_milieu(repo, info);
	else
		ft_dernier(repo, info);
	return (0);
}
