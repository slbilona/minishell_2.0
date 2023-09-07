/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:52:42 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/21 14:57:44 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static	char	**ft_free_split(char **str, int k)
{
	while (k >= 0)
	{
		free(str[k]);
		k--;
	}
	return (NULL);
}

static	int	ft_compte_mot(char const *s, char c)
{
	int	compte;
	int	i;

	i = 0;
	compte = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		if (s[i] != '\0')
			compte++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (compte);
}

static	int	ft_taille_mot(char const *s, char c, int i)
{
	int	taille;

	taille = 0;
	while (s[i])
	{
		if (s[i] != '\0' && (s[i] == c))
			return (taille);
		else
			taille++;
		i++;
	}
	return (taille);
}

static	void	ft_strncpy(char const *s, char *dest, int n, int i)
{
	int	k;

	k = 0;
	while (k < n)
	{
		dest[k] = s[i];
		i++;
		k++;
	}
	dest[k] = '\0';
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**dest;
	int		k;

	k = 0;
	i = 0;
	dest = (char **)malloc(sizeof(char *) * (ft_compte_mot(s, c) + 1));
	while (k < ft_compte_mot(s, c))
	{
		while (s[i] && (s[i] == c))
			i++;
		if ((s[i] != '\0') && (s[i] != c))
		{
			dest[k] = (char *)malloc((ft_taille_mot(s, c, i) + 1)
					* sizeof(char));
			if (!dest[k])
				return (ft_free_split(dest, k));
			ft_strncpy(s, dest[k], ft_taille_mot(s, c, i), i);
			i += ft_taille_mot(s, c, i);
			k++;
		}
	}
	dest[k] = NULL;
	return (dest);
}
