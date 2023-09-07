/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:31:15 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/29 16:31:17 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_d(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr_d(n * -1);
	}
	else if (0 <= n && n <= 9)
	{
		n = n + 48;
		write(1, &n, 1);
	}
	else if (n > 9)
	{
		ft_putnbr_d(n / 10);
		ft_putnbr_d(n % 10);
	}
}

int	ft_compte(int n)
{
	int	compte;

	compte = 0;
	if (n < 0)
	{
		compte ++;
		n = n * -1;
	}
	if (n >= 0 && n <= 9)
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

int	ft_put_d(va_list list)
{
	int	n;

	n = va_arg(list, int);
	ft_putnbr_d(n);
	return (ft_compte(n));
}
