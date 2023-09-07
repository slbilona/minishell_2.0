/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:18:34 by ilselbon          #+#    #+#             */
/*   Updated: 2023/03/13 21:23:04 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strchr(const char *s, int c)
{
	char	lettre;

	lettre = (char) c;
	if (*s == lettre)
		return (1);
	while (*s++)
	{
		if (*s == lettre)
			return (1);
	}
	return (0);
}
