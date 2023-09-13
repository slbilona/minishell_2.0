/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:05:51 by ilona             #+#    #+#             */
/*   Updated: 2023/09/13 22:51:52 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_count_double_string(char **str)
{
	int	i;
	//char **s;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_long_atoi(char *str, long long int *num)
{
	int	signe;
	int	i;

	signe = 1;
	i = 0;
	if (str)
	{
		while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				signe = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			if (*num > (LLONG_MAX - (str[i] - '0')) / 10)
				return (2);
			*num = *num * 10 + str[i] - 48;
			i++;
		}
	}
	*num = *num * signe;
	return (0);
}

void ft_deux()
{
	printf("fonction 2\n");
}

void ft_init_builtins()
{
	t_builtins builtins[2];
	
	builtins->ptr = {ft_exit, ft_deux};
	builtins->str = {"exit", "deux"};
}