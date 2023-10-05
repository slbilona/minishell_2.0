/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:05:51 by ilona             #+#    #+#             */
/*   Updated: 2023/10/06 00:35:15 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_count_double_string(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

int	ft_long_atoi(char *str, long long int *num)
{
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	if (str)
	{
		while (str[i] && ((9 <= str[i] && str[i] <= 13) || str[i] == ' '))
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

// Verifie que la string ne contient que des characteres numerique
int	ft_que_des_chiffres(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

//print un char ** en separent chaque string avec un espace
int	ft_print_tab(char **str, int j)
{
	while (str && str[j])
	{
		if (ft_strlen(str[j]) > 0)
		{
			if (write(STDOUT_FILENO, str[j], ft_strlen(str[j])) == -1)
				return (perror("Minishell: echo: erreur d'écriture "), 1);
			if (str[j + 1])
				if (write(STDOUT_FILENO, " ", 1) == -1)
					return (perror("Minishell: echo: erreur d'écriture "), 1);
		}
		j++;
	}
	return (0);
}

int	ft_signes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}
