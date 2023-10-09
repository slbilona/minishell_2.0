/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:48:28 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/09 18:18:24 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_new_compte_mot(const char *str, const char *sep)
{
	int	i;
	int	compte;

	i = 0;
	compte = 0;
	while (str && str[i])
	{
		while (str[i] && ft_strchr(sep, str[i]) && ft_quotes(str, i) == 0)
			i++;
		if (str[i])
			compte++;
		while (str[i] && (!ft_strchr(sep, str[i]) || ft_quotes(str, i) > 0))
			i++;
	}
	return (compte);
}

void	ft_new_strncpy(char const *str, char *dest, int n, int i)
{
	int	j;

	j = 0;
	while (j < n)
		dest[j++] = str[i++];
	dest[j] = '\0';
}

int	ft_new_taille_mot(const char *str, const char *sep, int i)
{
	int	taille;

	taille = 0;
	while (str && str[i])
	{
		if (str[i] && (ft_strchr(sep, str[i]) && ft_quotes(str, i) == 0))
			return (taille);
		else
			taille++;
		i++;
	}
	return (taille);
}

int	ft_new_split_suite(const char *str, const char *vrai_sep, char **dest)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < ft_new_compte_mot(str, vrai_sep))
	{
		while (str[i] && ft_strchr(vrai_sep, str[i]) && ft_quotes(str, i) == 0)
			i++;
		if (str[i] && (!ft_strchr(vrai_sep, str[i]) || ft_quotes(str, i) > 0))
		{
			dest[j] = malloc(sizeof(char)
					* (ft_new_taille_mot(str, vrai_sep, i) + 1));
			if (!dest[j])
				return (ft_free_split(dest, j), 1);
			ft_new_strncpy(str, dest[j],
				ft_new_taille_mot(str, vrai_sep, i), i);
			i += ft_new_taille_mot(str, vrai_sep, i);
			j++;
		}
	}
	dest[j] = NULL;
	return (0);
}

/* Comme split mais avec une liste de separateurs,
si sep est egal a NULL str sera split a chaque white spaces*/
char	**ft_new_split(const char *str, const char *sep)
{
	char		**dest;
	char		autre_sep[7];
	const char	*vrai_sep;

	if (!str)
		return (NULL);
	if (!sep)
	{
		ft_init_sep(autre_sep);
		vrai_sep = autre_sep;
	}
	else
		vrai_sep = sep;
	if (ft_new_compte_mot(str, vrai_sep) == 0)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_new_compte_mot(str, vrai_sep) + 1));
	if (ft_new_split_suite(str, vrai_sep, dest))
		return (NULL);
	return (dest);
}
