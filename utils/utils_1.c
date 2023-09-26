/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:05:51 by ilona             #+#    #+#             */
/*   Updated: 2023/09/23 11:20:31 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_count_double_string(char **str)
{
	int	i;

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

// Verifie que la string ne contient que des characteres numerique
int	ft_que_des_chiffres(char *str)
{
	int	i;

	i = 0;
	while (str[i])
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
	while (str[j])
	{
		if (write(STDOUT_FILENO, str[j], ft_strlen(str[j])) == -1)
			return (perror("Minishell: echo: erreur d'écriture "), 1);
		if (str[j + 1])
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (perror("Minishell: echo: erreur d'écriture "), 1);
		j++;
	}
	return (0);
}
