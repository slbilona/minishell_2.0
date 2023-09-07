/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:14:33 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/18 17:35:11 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	while (s[i])
		i++;
	dest = malloc((i + 1) * sizeof(char));
	if (dest)
	{
		j = 0;
		while (j < i)
		{
			dest[j] = s[j];
			j++;
		}
		dest[j] = '\0';
		return (dest);
	}
	return (NULL);
}
