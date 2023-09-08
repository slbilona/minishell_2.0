/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:52:42 by ilselbon          #+#    #+#             */
/*   Updated: 2023/09/08 20:54:26 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int ft_compte_espaces(char *str)
{
	int i;
	char c;
	int count;
	
	c = 0;
	count = 0;
	if(str)
	{
		i = 0;
		while(str[i])
		{
			if(ft_strchr("<>|", str[i]))
			{
				c = str[i];
				if(i > 0 && str[i - 1] != ' ')
					count++;
				while(str[i] == c)
					i++;
				if(str[i + 1] != 0 && str[i + 1] != ' ')
					count++;
				i++;
			}
			else
				i++;
		}
	}
	return count;
}

void ft_ajoute_espace(char *entree)
{
	printf("%d\n", ft_compte_espaces(entree));
//	malloc = (sizeof())
}