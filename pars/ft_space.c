/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:52:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/08 14:28:39 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_compte_espace_suite(int *i, int *count, char *str, char c)
{
	if (*i > 0 && str[*i - 1] != ' ')
		*count += 1;
	while (str && str[*i] == c)
		*i += 1;
	*i -= 1;
	if (str[*i + 1] != 0 && str[*i + 1] != ' '
		&& !ft_strchr("<>|", str[*i + 1]))
		*count += 1;
	*i += 1;
}

int	ft_compte_espaces(char *str)
{
	int		i;
	int		count;
	char	c;

	count = 0;
	if (str)
	{
		i = 0;
		while (str && str[i])
		{
			c = str[i];
			if (ft_quotes(str, i) == 3 || ft_quotes(str, i) == 4)
			{
				i++;
				while (str && str[i] && str[i] != c)
					i++;
				i++;
			}
			else if (ft_strchr("<>|", str[i]))
				ft_compte_espace_suite(&i, &count, str, c);
			else
				i++;
		}
	}
	return (count);
}

void	ft_ajoute_espaces_suite(char *s, char *str, int i, int j)
{
	char	c;

	while (s[i])
	{
		c = s[i];
		if (ft_quotes(s, i) == 3 || ft_quotes(s, i) == 4)
		{
			str[j++] = s[i++];
			while (s[i] && (ft_quotes(s, i) == 1 || ft_quotes(s, i) == 2))
				str[j++] = s[i++];
			str[j++] = s[i++];
		}
		else if (ft_strchr("<>|", s[i]))
		{
			if (i > 0 && s[i - 1] != ' ')
				str[j++] = ' ';
			while (s[i] && s[i] == c)
				str[j++] = s[i++];
			if (s[i] != 0 && s[i] != ' ' && !ft_strchr("<>|", s[i]))
				str[j++] = ' ';
		}
		else
			str[j++] = s[i++];
	}
	str[j] = 0;
}

char	*ft_ajoute_espace(char *entree)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!entree)
		return (NULL);
	str = malloc(sizeof(char)
			* (ft_compte_espaces(entree) + ft_strlen(entree) + 1));
	if (!str)
		return (NULL);
	ft_ajoute_espaces_suite(entree, str, i, j);
	free(entree);
	return (str);
}
