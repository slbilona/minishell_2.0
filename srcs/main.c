/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatamago <yatamago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/10/14 16:38:40 by yatamago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	g_exit_signaux = 0;

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
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, SIG_IGN);
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
