/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:39:35 by ilona             #+#    #+#             */
/*   Updated: 2023/09/14 23:19:06 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	main_parsing(char *str)
{
	if(check_direction(str))
		return(1);
	return (0);
}

int	check_direction(char *str)
{
	if(check_right_direction(str))
		return(1);
	if(check_left_direction(str))
		return(1);
	return (0);
}

int check_right_direction(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	
	while(str[i])
	{
		while(str[i] == '>')
		{
			j++;
			i++;
		}
		if(j >= 3)
		{
			if(j == 3)
				printf("bash: erreur de syntaxe près du symbole inattendu « > » \n\n");
			else
				printf("bash: erreur de syntaxe près du symbole inattendu « >> » \n\n");
			
			return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}

int check_left_direction(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	
	while(str[i])
	{
		while(str[i] == '<')
		{
			j++;
			i++;
		}
		if(j >= 4)
		{
			if(j == 4)
				printf("bash: erreur de syntaxe près du symbole inattendu « < » \n\n");
			else
				printf("bash: erreur de syntaxe près du symbole inattendu « << » \n\n");
			return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_pre_parsing(char *entree)
{
	char	*n_entree;

	n_entree = ft_ajoute_espace(entree);
	if (!n_entree)
		return (NULL);
	return (n_entree);
}
