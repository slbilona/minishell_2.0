/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:49:05 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/21 18:15:06 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	j;
	char			*news;

	j = 0;
	if (ft_strlen(s) <= start)
	{
		news = malloc(sizeof(char));
		news[0] = 0;
		return (news);
	}
	while (s[start + j] && j < len)
		j++;
	news = malloc((j + 1) * sizeof(char));
	if (news)
	{
		j = 0;
		while (j < (len) && s[start + j])
		{
			news[j] = s[start + j];
			j++;
		}
		news[j] = '\0';
		return (news);
	}
	return (NULL);
}
