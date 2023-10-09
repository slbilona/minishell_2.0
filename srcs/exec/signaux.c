/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:29 by soleil            #+#    #+#             */
/*   Updated: 2023/10/09 18:18:24 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	handle_sigint(int sig)
{
	//printf("\n");
	if(sig == 2)
	{
		//printf("🐙 Minishell$ ");
		printf("\nCtrl+C a été pressé. Nouveau prompt : \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// j'ai juste fait ca vite fait pck j'avais besoin d'un truc pour arreter le programme mtn qu'il n'y a plus de ctrl c
void	ft_ctrl_d(t_info *info, char *entree)
{
	if (!entree)
	{
		ft_free_struct(NULL, info, 1);
		exit(0);
	}
}
  