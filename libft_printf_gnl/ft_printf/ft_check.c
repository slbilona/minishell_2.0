/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:28:53 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/29 18:49:14 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
