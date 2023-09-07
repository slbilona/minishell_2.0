/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:31:24 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/29 16:31:30 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
