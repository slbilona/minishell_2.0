/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:31:47 by ilselbon          #+#    #+#             */
/*   Updated: 2023/08/10 18:15:24 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_u(unsigned int n)
{
	if (0 == n || (1 <= n && n <= 9))
	{
		n = n + 48;
		write(1, &n, 1);
	}
	else if (9 < n)
	{
		ft_putnbr_u(n / 10);
		ft_putnbr_u(n % 10);
	}
}

int	ft_compte_u(unsigned int n)
{
	int	compte;

	compte = 0;
	if (n == 0 || (1 <= n && n <= 9))
	{
		compte++;
		return (compte);
	}
	else
	{
		while (n != 0)
		{
			n = n / 10;
			compte++;
		}
		return (compte);
	}
	return (compte);
}

int	ft_put_u(va_list list)
{
	unsigned int	n;

	n = va_arg(list, unsigned int);
	ft_putnbr_u(n);
	return (ft_compte_u(n));
}

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
