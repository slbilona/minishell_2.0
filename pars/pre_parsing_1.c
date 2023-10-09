/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:22:56 by ilona             #+#    #+#             */
/*   Updated: 2023/10/09 17:23:37 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*Verifie le nombre de quotes, le nombre
de chevrons et le nombre de pipes*/
int	main_parsing(char *str)
{
	if (ft_quotes(str, 0) == -1)
	{
		ft_put_str_error("Minishell:", " guillemet", " non", " fermé");
		return (1);
	}
	if (check_right_direction(str))
		return (1);
	if (check_left_direction(str))
		return (1);
	if (ft_check_pipe(str))
		return (1);
	return (0);
}

int	ft_check_pipe(char *str)
{
	if (ft_check_pipe_prems(str) == 1 || ft_check_pipe_suite(str) == 1)
	{
		ft_put_str_error("Minishell: ", "syntax error ",
			"near unexpected ", "token `|'");
		return (1);
	}
	else if (ft_check_pipe_prems(str) == 1 || ft_check_pipe_suite(str) == 2)
	{
		ft_put_str_error("Minishell: ", "syntax error ",
			"near unexpected ", "token `||'");
		return (1);
	}
	return (0);
}
