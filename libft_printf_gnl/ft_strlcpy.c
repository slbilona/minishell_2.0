/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:25:12 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/21 18:04:17 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(src) < size)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else if (size > 0)
	{
		while ((size - 1) != 0)
		{
			dst[i] = src[i];
			size--;
			i++;
		}
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
