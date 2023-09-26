/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:31:19 by ilona             #+#    #+#             */
/*   Updated: 2023/09/26 16:16:31 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_guillemet_simple(char *str, int *i_str, int *j, int *k)
{
	i_str[*k] = 3;
	*k += 1;
	*j += 1;
	while (str && str[*j] && str[*j] != '\'')
	{
		i_str[*k] = 1;
		*k += 1;
		*j += 1;
	}
	if (!str[*j])
		return (-1);
	else if (str[*j] == '\'')
	{
		i_str[*k] = 3;
		*k += 1;
		*j += 1;
	}
	return (0);
}

int	ft_double_guillemet(char *str, int *i_str, int *j, int *k)
{
	i_str[*k] = 4;
	*k += 1;
	*j += 1;
	while (str && str[*j] && str[*j] != '\"')
	{
		i_str[*k] = 2;
		*k += 1;
		*j += 1;
	}
	if (!str[*j])
		return (-1);
	else if (str[*j] == '\"')
	{
		i_str[*k] = 4;
		*k += 1;
		*j += 1;
	}
	return (0);
}

/* Renvoie -1 si un guillemet n'est pas fermé
Renvoie 0 si str[i] est à l'extérieur de guillemets
Renvoie 1 si str[i] est à l'intérieur de guillemets simples
Renvoie 2 si str[i] est à l'intérieur de guillemets doubles
Renvoie 3 si str[i] est un guillemet simple
Renvoie 4 si str[i] est un guillemet double */
int	ft_quotes(char *str, int i)
{
	int	j;
	int	k;
	int	ret;
	int	*i_str;

	j = 0;
	k = 0;
	i_str = malloc(sizeof(int) * ft_strlen(str));
	if (!i_str)
		return (-1);
	while (str && str[j])
	{
		if (str[j] == '\"')
		{
			if (ft_double_guillemet(str, i_str, &j, &k) == -1)
				return (free(i_str), -1);
		}
		else if (str[j] == '\'')
		{
			if (ft_guillemet_simple(str, i_str, &j, &k) == -1)
				return (free(i_str), -1);
		}
		else
		{
			i_str[k++] = 0;
			j++;
		}
	}
	ret = i_str[i];
	return (free(i_str), ret);
}
