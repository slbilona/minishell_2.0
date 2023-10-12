/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:29 by soleil            #+#    #+#             */
/*   Updated: 2023/10/12 20:45:02 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_signaux()
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigint(int sig)
{
	// if (g_exit_signaux != 0)
	// {
		if (write(1, "\n", 1) == -1)
		{
			perror("Minishell: erreur d'écriture ");
			return ;
		}
	//}
	if (sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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

void ft_remet_signaux()
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
