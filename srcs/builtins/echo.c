/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:06:31 by ilona             #+#    #+#             */
/*   Updated: 2023/10/09 18:18:24 by ilona            ###   ########.fr       */
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
			if (repo->args[*i][*j] == 0)
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

//pb lorsqu'on redirige et qu'on utilise l'argument -n
int	ft_echo(t_struct *repo, void *inf)
{
	int	i;
	int	j;
	int	n;

	(void)inf;
	j = 1;
	i = 1;
	n = 1;
	ft_option_n(repo, &n, &j, &i);
	if (ft_print_tab(repo->args, i))
		return (1);
	if (n == 1 || j == 1)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("Minishell: echo: erreur d'écriture "), 1);
	return (0);
}