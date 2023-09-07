/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:29:02 by ilselbon          #+#    #+#             */
/*   Updated: 2023/08/10 18:15:11 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_suite2(const char *str, int cmp, va_list list)
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
	cmp = ft_suite2(str, cmp, list);
	va_end(list);
	return (cmp);
}

int	ft_check(char c, va_list list)
{
	if (c == 'c')
		return (ft_put_c(list));
	else if (c == 's')
		return (ft_put_s(list));
	else if (c == 'd' || c == 'i')
		return (ft_put_d(list));
	else if (c == 'u')
		return (ft_put_u(list));
	else if (c == 'x')
		return (ft_put_x(list));
	else if (c == 'X')
		return (ft_put_xmaj(list));
	else if (c == 'p')
		return (ft_put_p(list));
	else if (c == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
