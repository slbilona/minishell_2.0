/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:40:33 by ilselbon          #+#    #+#             */
/*   Updated: 2022/11/21 13:36:53 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static	int	ft_compte(int n)
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

static	char	*ft_int_min(char *str)
{
	if (str)
	{
		str[0] = '-';
		str[1] = '2';
		str[2] = '1';
		str[3] = '4';
		str[4] = '7';
		str[5] = '4';
		str[6] = '8';
		str[7] = '3';
		str[8] = '6';
		str[9] = '4';
		str[10] = '8';
		str[11] = '\0';
	}
	return (str);
}

static	void	ft_str(int n, char *str, int i)
{
	int	j;

	j = 0;
	str[i] = '\0';
	if (n < 0)
	{
		n = n * -1;
		str[j++] = '-';
	}
	while (j < i--)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;

	if (n == -2147483648)
	{
		str = malloc(sizeof(char) * 12);
		return (ft_int_min(str));
	}
	i = ft_compte(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str)
	{
		ft_str(n, str, i);
	}
	return (str);
}
