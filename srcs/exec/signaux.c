/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleil <soleil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:29 by soleil            #+#    #+#             */
/*   Updated: 2023/10/11 21:48:32 by soleil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	handle_sigint(int sig)
{
	
	if (write(1, "\n", 1) == -1)
	{
		perror("Minishell: erreur d'écriture ");
		return ;
	}
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
