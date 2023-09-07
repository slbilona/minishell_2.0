/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:40:02 by ilselbon          #+#    #+#             */
/*   Updated: 2023/02/18 18:55:48 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static	int	ft_verif(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_compte_strtrim(char const *str, char const *set, int *i)
{
	int	j;

	*i = 0;
	j = 0;
	while (str[*i] && (ft_verif(str[*i], set) == 1))
		*i += 1;
	while (str[j] != 0)
		j++;
	j--;
	while (str[j] && (ft_verif(str[j], set) == 1))
		j--;
	return (j - *i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*news;
	int		i;
	int		j;
	int		taille;

	taille = ft_compte_strtrim(s1, set, &i);
	if (taille <= 0)
		return (ft_strdup(""));
	news = malloc((taille + 1) * sizeof(char));
	j = 0;
	if (news)
	{
		while (s1[i] && j < taille)
		{
			news[j] = s1[i];
			i++;
			j++;
		}
		news[j] = '\0';
		return (news);
	}
	return (NULL);
}
