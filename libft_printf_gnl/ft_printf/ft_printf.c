/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:29:02 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/30 18:44:34 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_suite(const char *str, int cmp, va_list list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			j = ft_check(str[i + 1], list);
			if (j >= 0)
			{
				i += 2;
				cmp = cmp + j;
			}
			else
				return (-1);
		}
		else
		{
			write(1, &str[i++], 1);
			cmp++;
		}
	}
	return (cmp);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		cmp;

	cmp = 0;
	va_start(list, str);
	cmp = ft_suite(str, cmp, list);
	va_end(list);
	return (cmp);
}
