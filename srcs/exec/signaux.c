/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatamago <yatamago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:29 by soleil            #+#    #+#             */
/*   Updated: 2023/10/14 16:38:27 by yatamago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_exit_signaux != 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_exit_signaux = 130;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}



void	ft_ctrl_d(t_info *info, char *entree)
{
	if (!entree)
	{
		if (write(1, "exit\n", 5) == -1)
		{
			perror("Minishell: erreur d'écriture ");
			return ;
		}
		ft_free_struct(NULL, info, 1);
		exit(0);
	}
}

void	ft_ctrl_c_heredoc(int sig)
{
	(void)sig;
	g_exit_signaux = 130;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "> \n", 3);
}

int	ft_signaux_heredoc(t_info *info, int fd)
{
	if (g_exit_signaux == 130)
	{
		close(fd);
		unlink("/tmp/heredoc.txt");
		dup2(info->saved_stdin, STDIN_FILENO);
		return (1);
	}
	return (0);
}

void	ft_signaux_exit(t_info *info, int status)
{
	int	exit_signal;

	exit_signal = WTERMSIG(status);
	if (exit_signal == SIGINT)
	{
		if (!info->ctrl_c_triggered)
		{
			write(info->saved_stdout, "\n", 1);
			info->ctrl_c_triggered = 1;
		}
		g_exit_signaux = 130;
		info->exit = 130;
	}
	else if (exit_signal == SIGQUIT)
	{
		g_exit_signaux = 131;
		info->exit = 131;
	}
}
