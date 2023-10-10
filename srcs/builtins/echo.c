/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:06:31 by ilona             #+#    #+#             */
/*   Updated: 2023/10/10 18:09:28 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_option_n(t_struct *repo, int *n, int *j, int *i)
{
	while (repo->args && repo->args[*i])
	{
		if (repo->args[*i][0] == '-')
		{
			*j = 1;
			while (repo->args[*i][*j] == 'n')
				*j += 1;
			if (repo->args[*i][*j - 1] && repo->args[*i][*j - 1]
				== 'n' && repo->args[*i][*j] == 0)
			{
				*j = 0;
				*i += 1;
				*n = 0;
			}
			else
			{
				*j = 0;
				break ;
			}
		}
		else
			break ;
	}
}

int	ft_echo(t_struct *repo, void *inf)
{
	int		i;
	int		j;
	int		n;
	int		o;
	t_info	*info;

	info = inf;
	o = info->i;
	j = 1;
	i = 1;
	n = 1;
	ft_option_n(&repo[o], &n, &j, &i);
	if (ft_print_tab(repo[o].args, i))
		return (1);
	if (n == 1 || j == 1)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("Minishell: echo: erreur d'écriture "), 1);
	return (0);
}
