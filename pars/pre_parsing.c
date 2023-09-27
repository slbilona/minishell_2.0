/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:39:35 by ilona             #+#    #+#             */
/*   Updated: 2023/09/27 14:23:48 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	main_parsing(char *str)
{
	if (ft_quotes(str, 0) == -1) // si il y a un guillemet non fermé
		return (1);
	if(check_direction(str))
		return(1);
	if(check_pipe(str))
		return (1);
	return (0);
}

int  check_pipe(char *str)
{
     int i;
     int j;
     int k;

     i = 0;
     j = 0;
     k = 0;     
     while(str[i])
     {
          if(str[i] == '|')
          {
               j = i;
               while(str[j])
               {
                    if((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= '0' && str[j] <= '9'))
                    {
						
                         k = 1;
                    }
                    j++;
               }
			if(k == 0)
               return(1);
          }
          i++;
     }
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
	while(str && str[i])
	{
		while(str[i] == '>')
		{
			j++;
			i++;
		}
		if(j >= 3)
		{
			if(j == 3)
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `>'", NULL);
			else
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `>>'", NULL);
			
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
	
	while(str && str[i])
	{
		while(str[i] == '<')
		{
			j++;
			i++;
		}
		if(j >= 4)
		{
			if(j == 4)
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `<'", NULL);
			else
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `<<'", NULL);
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
