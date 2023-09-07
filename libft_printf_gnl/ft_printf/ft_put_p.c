/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:18:30 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/30 12:18:31 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_x(unsigned long n)
{
	char	*base;
	int		cmp;

	cmp = 0;
	base = "0123456789abcdef";
	if (0 == n || (1 <= n && n <= 15))
	{
		write(1, &base[n], 1);
		cmp += 1;
	}
	else if (n >= 16)
	{
		cmp = cmp + ft_putnbr_x(n / 16);
		cmp = cmp + ft_putnbr_x(n % 16);
	}
	return (cmp);
}

int	ft_put_p(va_list list)
{
	long	n;

	n = (unsigned long)va_arg(list, unsigned long);
	if (n > 0)
	{
		write(1, "0x", 2);
		return (2 + ft_putnbr_x(n));
	}
	else if (n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		return (2 + ft_putnbr_x((unsigned long)n));
	}
}
