/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:39:35 by ilona             #+#    #+#             */
/*   Updated: 2023/10/06 11:19:32 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"
int ft_check_pipe(char *str);
int	main_parsing(char *str)
{
	if (ft_quotes(str, 0) == -1) // si il y a un guillemet non fermé
		return (1);
	if (check_direction(str))
		return(1);
	if (ft_check_pipe(str))
		return (1);
	// if (check_pipe(str))
	// 	return (1);
	return (0);
}

int ft_check_pipe(char *str)
{
	int i;
	int k;
	int j;
	int o;
	int prems;
	int count_pipe;

	i = 0;
	k = 0;
	prems = 0;
	while (str && str[i])
	{
		o = 0;
		while((9 <= str[i] && str[i] <= 13) || str[i] == 32 || str[i] == '>' || str[i] == '<')
			i++;
		if (str[i] == '|')
		{
			if (prems == 0)
			{
				if (str[i + 1] && str[i + 1] == '|')
					k = 2;
				else
					k = 1;
			}
			j = i + 1;
			count_pipe = 1;
			while (str[j] && str[j] == '|')
			{
				count_pipe++;
				j++;
			}
			while ((9 <= str[j] && str[j] <= 13) || str[j] == 32 || str[j] == '>' || str[j] == '<')
			{
				//if (str[j] == '>' || str[j] == '<')
					o++;
				j++;
			}
			if ((!str[j] && o == 0) || count_pipe > 1 || k > 0 || (o > 0 && str[j] == '|'))
			{
				if ((str[j] && str[j + 1] && str[j + 1] == '|') || count_pipe >= 2 || k == 2)
					ft_put_str_error("Minishell: ", "syntax error ", "near unexpected ", "token `||'");
				else
					ft_put_str_error("Minishell: ", "syntax error ", "near unexpected ", "token `|'");
				return (1);
			}
		}
		else
			prems++;
		if (str[i])
			i++;
	}
	return (0);
}

int  check_pipe(char *str)
{
	int i;
	int j;
	int k;
	int count_pipe;

	count_pipe = 0;
	i = 0;
	j = 0;
	k = 0;     
	while (str && str[i])
	{
		if (str[i] == '|')
		{
			count_pipe = 1;
			j = i + 1;
			while (str[j])
			{
				if (str[j] == '|')
				{
					count_pipe++;
				}
				else if ((str[j] >= 'a' && str[j] <= 'z') || (str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= '0' && str[j] <= '9'))
				{
					k = 1;
					count_pipe = 1;
				}
				j++;
			}
			if (count_pipe >= 3)
			{
				ft_put_str_error("syntax error ", "near unexpected ", "token `||'", NULL);
				return(1);
			}
			if (count_pipe == 2 || k == 0)
			{
				ft_put_str_error("syntax error ", "near unexpected ", "token `|'", NULL);
				return(1);
			}
		}
		i++;
	}
	return (0);
}

int	check_direction(char *str)
{
	if (check_right_direction(str))
		return(1);
	if (check_left_direction(str))
		return(1);
	return (0);
}

int check_right_direction(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i] == '>')
		{
			j++;
			i++;
		}
		if (j >= 3)
		{
			if (j == 3)
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `>'", NULL);
			else
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `>>'", NULL);
			
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int check_left_direction(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i] && str[i] == '<')
		{
			j++;
			i++;
		}
		if (j >= 3)
		{
			if (j == 3)
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `<'", NULL);
			else
				ft_put_str_error("Minishell: syntax ", "error near ", "unexpected token `<<'", NULL);
			return (1);
		}
		if(str[i])
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
