/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_Xmaj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:32:51 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/29 16:32:52 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_xmaj(unsigned int n)
{
	char	*base;
	int		cmp;

	cmp = 0;
	base = "0123456789ABCDEF";
	if (0 == n || (1 <= n && n <= 15))
	{
		write(1, &base[n], 1);
		cmp += 1;
	}
	else if (n >= 16)
	{
		cmp = cmp + ft_putnbr_xmaj(n / 16);
		cmp = cmp + ft_putnbr_xmaj(n % 16);
	}
	return (cmp);
}

int	ft_put_xmaj(va_list list)
{
	int	n;

	n = va_arg(list, int);
	if (n >= 0)
		return (ft_putnbr_xmaj(n));
	else
	{
		ft_putnbr_xmaj((unsigned int)n);
		return (8);
	}
}
