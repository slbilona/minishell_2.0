/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_c_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:30:41 by ilselbon          #+#    #+#             */
/*   Updated: 2023/08/10 18:16:17 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_c(va_list list)
{
	int	c;

	c = va_arg(list, int);
	write (1, &c, 1);
	return (1);
}

int	ft_put_s(va_list list)
{
	char	*str;
	int		i;
	int		cmp;

	str = va_arg(list, char *);
	i = 0;
	cmp = 0;
	if (str)
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			i++;
			cmp++;
		}
	}
	else
	{
		write(1, "(null)", 6);
		cmp += 6;
	}
	return (cmp);
}
