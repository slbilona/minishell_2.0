/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:48:36 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/07 20:01:06 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*news;
	int		i;
	int		j;

	i = 0;
	j = 0;
	news = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (news)
	{
		while (s1 && s1[i])
			news[j++] = s1[i++];
		i = 0;
		while (s2 && s2[i])
			news[j++] = s2[i++];
		news[j] = '\0';
		return (news);
	}
	return (NULL);
}
