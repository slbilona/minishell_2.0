/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:52:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/09/16 23:52:16 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

//creer une fonctioon qui nous indique si on est dans des guillemets ou non

int	ft_compte_espaces(char *str)
{
	int		i;
	int		count;
	char	c;

	c = 0;
	count = 0;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			c = str[i];
			if (ft_strchr("\"\'", str[i]))
			{
				// if (i > 0 && str[i - 1] != ' ' && !ft_strchr("<>|", str[i - 1]))
				// 	count++;
				i++;
				while (str[i] && str[i] != c)
					i++;
				i++;
			}
			else if (ft_strchr("<>|", str[i]))
			{
				if (i > 0 && str[i - 1] != ' ')
					count++;
				while (str[i] == c)
					i++;
				i--;
				if (str[i + 1] != 0 && str[i + 1] != ' ' && !ft_strchr("<>|", str[i + 1]))
					count++;
				i++;
			}
			else
				i++;
		}
	}
	return (count);
}

char	*ft_ajoute_espace(char *entree)
{
	int		i;
	int		j;
	char	c;
	char	*str;

	i = 0;
	j = 0;
	if (!entree)
		return (NULL);
	str = malloc(sizeof(char) * (ft_compte_espaces(entree) + ft_strlen(entree) + 1));
	if (!str)
		return (NULL);
	while (entree[i])
	{
		c = entree[i];
		if (ft_strchr("\"\'", entree[i]))
		{
			// if (i > 0 && entree[i - 1] != ' ' && !ft_strchr("<>|", entree[i - 1]))
			// {
			// 	str[j] = ' ';
			// 	j++;
			// }
			str[j++] = entree[i++];
			while (entree[i] && entree[i] != c)
				str[j++] = entree[i++];
			str[j++] = entree[i++];
		}
		else if (ft_strchr("<>|", entree[i]))
		{
			if (i > 0 && entree[i - 1] != ' ')
				str[j++] = ' ';
			while (entree[i] && entree[i] == c)
				str[j++] = entree[i++];
			if (entree[i] != 0 && entree[i] != ' ' && !ft_strchr("<>|", entree[i]))
				str[j++] = ' ';
		}
		else
			str[j++] = entree[i++];
	}
	str[j] = 0;
	free(entree);
	return (str);
}
