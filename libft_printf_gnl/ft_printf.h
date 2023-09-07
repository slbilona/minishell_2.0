/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:30:51 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/29 18:49:50 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_check(char c, va_list list);
int	ft_put_c(va_list list);
int	ft_put_s(va_list list);
int	ft_put_d(va_list list);
int	ft_putchar(char c);
int	ft_put_u(va_list list);
int	ft_compte(int n);
int	ft_put_x(va_list list);
int	ft_put_xmaj(va_list list);
int	ft_put_p(va_list list);
int	ft_printf(const char *str, ...);
#endif
