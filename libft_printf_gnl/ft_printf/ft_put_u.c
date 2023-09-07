/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:31:47 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/29 16:31:48 by ilselbon         ###   ########.fr       */
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
