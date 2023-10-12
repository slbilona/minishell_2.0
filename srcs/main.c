/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleil <soleil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/10/12 21:46:50 by soleil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int g_exit_signaux = 0;

void	ft_init_globale(t_info *info)
{
	if (g_exit_signaux != 0)
		info->exit = g_exit_signaux;
	g_exit_signaux = 0;
}

int	main(int ac, char **av, char **env)
{
	char		*entree;
	t_info		*info;
	
	(void) av;
	if (ac == 1)
	{
		info = ft_init_info(env);
		if (!info)
			return (1);
		while (1)
		{
			signal(SIGINT,handle_sigint);
			entree = readline("🐙 Minishell$ ");
			ft_ctrl_d(info, entree);
			ft_init_globale(info);
			if (ft_strlen(entree) == 0)
				info->exit = 0;
			else
				if (parsing_exec(info, entree))
					info->exit = 2;
		}
		ft_free_struct(NULL, info, 1);
	}
	return (0);
}
