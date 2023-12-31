/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:04:59 by ilona             #+#    #+#             */
/*   Updated: 2023/10/14 18:07:07 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_processus_fils_suite(t_info *info, t_struct *repo, int i)
{
	if (repo[i].cmd && ft_builtins_ou_non(&repo[i], info))
	{
		repo[i].path = ft_cherche_path(&repo[i], info);
		if (!repo[i].path)
			ft_erreur_path(info, repo);
	}
	if (info->nb_de_pipe > 0)
		if (ft_pipe(&repo[i], info))
			ft_put_str_error("Minishell: ", "erreur lors de ",
				"la redirection", " des pipes");
}

void	ft_processus_fils(t_info *info, t_struct *repo,
	int redir)
{
	int	i;
	int	ex;

	i = info->i;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_processus_fils_suite(info, repo, i);
	if (repo[i].redirection)
		redir = ft_redirection(repo[i].redirection);
	if (repo[i].cmd && !redir && ft_builtins_pipe(repo, info))
		ft_execve(&repo[i], info);
	if (redir)
		ex = redir;
	else
		ex = repo[i].ret;
	ft_free_pipe(info);
	ft_free_struct(repo, info, 2);
	exit(ex);
}

int	ft_fork(t_struct *repo, t_info *info)
{
	int		i;
	int		redir;

	i = info->i;
	signal(SIGINT, SIG_IGN);
	redir = 0;
	info->fork = 1;
	info->diff_pid[repo[i].nb_cmd] = fork();
	if (info->diff_pid[repo[i].nb_cmd] == -1)
	{
		info->fork = 0;
		info->exit = 1;
		return (perror("Minishell: fork"), 1);
	}
	else if (info->diff_pid[repo[i].nb_cmd] == 0)
		ft_processus_fils(info, repo, redir);
	else
	{
		if (info->nb_de_pipe && repo[i].nb_cmd > 0)
		{
			close(info->pipe_fd[repo[i].nb_cmd - 1][0]);
			close(info->pipe_fd[repo[i].nb_cmd - 1][1]);
		}
	}
	return (0);
}
