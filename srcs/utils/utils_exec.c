/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:09:59 by ilona             #+#    #+#             */
/*   Updated: 2023/10/14 16:30:22 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_verif_pipe_fd(t_info *info, t_struct *repo)
{
	if (!info->pipe_fd)
	{
		ft_put_str_error("Minishell: ", "pipe: erreur",
			" lors de", " l'allocation");
		free(info->diff_pid);
		info->i_diff_pid = 0;
		dup2(info->saved_stdout, STDOUT_FILENO);
		dup2(info->saved_stdin, STDIN_FILENO);
		ft_free_struct(repo, info, 0);
		info->exit = 1;
		return (1);
	}
	return (0);
}

int	ft_heredoc(t_info *info, t_struct *repo)
{
	if (ft_heredoc_ou_non(repo[info->i].redirection))
	{
		if (ft_heredoc_deux(info, repo[info->i].redirection))
		{
			free(info->diff_pid);
			info->i_diff_pid = 0;
			ft_free_pipe(info);
			dup2(info->saved_stdout, STDOUT_FILENO);
			dup2(info->saved_stdin, STDIN_FILENO);
			ft_free_struct(repo, info, 0);
			return (1);
		}
	}
	return (0);
}

void	ft_wait(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	info->ctrl_c_triggered = 0;
	while (i < info->nb_de_cmd && info->diff_pid[i])
	{
		waitpid(info->diff_pid[i], &status, 0);
		if (WIFEXITED(status))
			info->exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			ft_signaux_exit(info, status);
		}
		i++;
	}
}

void	ft_erreur_path(t_info *info, t_struct *repo)
{
	int	i;
	int	ret;

	i = info->i;
	info->fork = 0;
	ret = 127 - ft_dir_ou_non(repo[i].cmd);
	if (ft_dir_ou_non(repo[i].cmd))
		ft_put_str_error("Minishell: ", repo[i].cmd,
			" : est un dossier", NULL);
	else
		ft_put_str_error("Minishell: ", repo[i].cmd,
			" : commande introuvable", NULL);
	ft_free_pipe(info);
	ft_free_struct(repo, info, 2);
	exit(ret);
}

/* Verifie si la commande fait partie des builtins.
Si c'est le cas la fonction associée est appellée */
int	ft_builtins_ou_non(t_struct *repo, t_info *info)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(repo->cmd, info->builtins[i].str,
				ft_strlen(repo->cmd)) == 0
			&& ft_strncmp(repo->cmd, info->builtins[i].str,
				ft_strlen(info->builtins[i].str)) == 0)
			return (0);
		i++;
	}
	return (1);
}
