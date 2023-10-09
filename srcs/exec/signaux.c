/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleil <soleil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:29 by soleil            #+#    #+#             */
/*   Updated: 2023/10/09 21:38:00 by soleil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	handle_sigint(int sig)
{
	printf("\n");
	if(sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// j'ai juste fait ca vite fait pck j'avais besoin d'un truc pour arreter le programme mtn qu'il n'y a plus de ctrl c (y'a des leaks pour l'instant)
void	ft_ctrl_d(char *entree, t_info *info)
{
	int j = 1;
	if (!entree)
	{
		ft_free_struct(NULL,info,j);
		exit(0);
	}
}
  