/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:51:25 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/23 17:52:55 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	l;

	l = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == l)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
