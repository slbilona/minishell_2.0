/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:39:35 by ilona             #+#    #+#             */
/*   Updated: 2023/10/09 18:18:24 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_check_pipe_suite_2(int i, char *str, int *o, int count_pipe)
{
	int	j;

	j = i + 1;
	count_pipe = 1;
	while (str[j] && str[j] == '|')
	{
		count_pipe++;
		j++;
	}
	while ((9 <= str[j] && str[j] <= 13) || str[j] == 32
		|| str[j] == '>' || str[j] == '<')
	{
		*o += 1;
		j++;
	}
	if ((!str[j] && *o == 0) || count_pipe > 1
		|| (*o > 0 && str[j] == '|'))
	{
		if ((str[j] && str[j + 1] && str[j + 1] == '|')
			|| count_pipe >= 2)
			return (2);
		else
			return (1);
	}
	return (0);
}

int	ft_check_pipe_suite(char *str)
{
	int	i;
	int	o;
	int	count_pipe;
	int	ret;

	i = 0;
	count_pipe = 0;
	while (str && str[i])
	{
		o = 0;
		while ((9 <= str[i] && str[i] <= 13) || str[i] == 32
			|| str[i] == '>' || str[i] == '<')
			i++;
		if (str[i] == '|')
		{
			ret = ft_check_pipe_suite_2(i, str, &o, count_pipe);
			if (ret != 0)
				return (ret);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	ft_check_pipe_prems(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		while ((9 <= str[i] && str[i] <= 13) || str[i] == 32
			|| str[i] == '>' || str[i] == '<')
			i++;
		if (str[i] == '|')
		{
			if (str[i + 1] && str[i + 1] == '|')
				return (2);
			else
				return (1);
		}
		break ;
	}
	return (0);
}

int	check_right_direction(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i] && str[i++] == '>')
			j++;
		if (j >= 3)
		{
			if (j == 3)
				ft_put_str_error("Minishell: syntax ", "error near ",
					"unexpected token `>'", NULL);
			else
				ft_put_str_error("Minishell: syntax ", "error near ",
					"unexpected token `>>'", NULL);
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	check_left_direction(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i] && str[i++] == '<')
			j++;
		if (j >= 3)
		{
			if (j == 3)
				ft_put_str_error("Minishell: syntax ", "error near ",
					"unexpected token `<'", NULL);
			else
				ft_put_str_error("Minishell: syntax ", "error near ",
					"unexpected token `<<'", NULL);
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
