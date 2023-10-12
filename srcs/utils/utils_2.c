/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:23 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/12 18:26:57 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	**ft_supprime_sous_chaine(char **str, int i)
{
	int		j;
	int		k;
	char	**s;

	j = 0;
	k = 0;
	s = malloc(sizeof(char *) * ft_count_double_string(str));
	if (!s)
		return (NULL);
	while (str && str[k])
	{
		if (k == i)
			k++;
		else
		{
			s[j] = ft_strdup(str[k]);
			if (!s[j])
				return (ft_free_split(s, j), NULL);
			j++;
			k++;
		}
	}
	s[j] = NULL;
	ft_free_double_string(str);
	return (s);
}

// Ecrit les char * qu'on lui envoie dans la sortie d'erreur
void	ft_put_str_error(char *str1, char *str2, char *str3, char *str4)
{
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	if (str4)
		write(2, str4, ft_strlen(str4));
	write(2, "\n", 1);
}

int	ft_directory_ou_non(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
	}
	return (0);
}

int	ft_white_space_2(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_quotes(str, i) == 0 && ((9 <= str[i]
					&& str[i] <= 13) || str[i] == 32))
			return (1);
		i++;
	}
	return (0);
}
