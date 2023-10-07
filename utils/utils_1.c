/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:05:51 by ilona             #+#    #+#             */
/*   Updated: 2023/10/07 12:59:47 by ilona            ###   ########.fr       */
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
