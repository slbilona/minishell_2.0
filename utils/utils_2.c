/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:23 by ilselbon          #+#    #+#             */
/*   Updated: 2023/09/19 14:45:23 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

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
