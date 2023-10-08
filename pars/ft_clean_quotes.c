/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 00:57:38 by ilona             #+#    #+#             */
/*   Updated: 2023/10/08 13:59:32 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_q_taille(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str && str[i])
	{
		if (ft_quotes(str, i) == 3 || ft_quotes(str, i) == 4)
			ret++;
		i++;
	}
	return (ft_strlen(str) - ret);
}

void	ft_clean_quotes_suite(char *str, char *s)
{
	int	k;
	int	j;

	j = 0;
	k = 0;
	while (str && str[j])
	{
		if (ft_quotes(str, j) == 3 || ft_quotes(str, j) == 4)
			j++;
		else
			s[k++] = str[j++];
	}
}

// Retire les guillemets ouvrant et fermant de str
char	**ft_clean_quotes(char **str)
{
	int		i;
	int		taille;
	char	**s;

	i = 0;
	s = malloc(sizeof(char *) * (ft_count_double_string(str) + 1));
	if (!s)
		return (NULL);
	while (str && str[i])
	{
		taille = ft_q_taille(str[i]);
		s[i] = malloc(sizeof(char) * (taille + 1));
		if (!s[i])
			return (ft_free_split(s, i));
		ft_clean_quotes_suite(str[i], s[i]);
		s[i][taille] = 0;
		i++;
	}
	s[i] = NULL;
	ft_free_double_string(str);
	return (s);
}
