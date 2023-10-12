/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:20:23 by ilona             #+#    #+#             */
/*   Updated: 2023/10/12 14:20:48 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_cherche_redirection(t_struct *repo, char **s, int *j, int i)
{
	char	*str_joined;

	str_joined = ft_strjoin(s[*j], " ");
	repo[i].redirection = mange(repo[i].redirection,
			ft_strjoin(str_joined, s[*j + 1]), 1);
	free(str_joined);
	*j += 2;
	return (0);
}

int	ft_verif_chevrons(char **s)
{
	int	j;

	j = -1;
	while (s[++j])
	{
		if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0 || ft_strncmp(s[j], ">>",
				sizeof(s[j])) == 0 || ft_strncmp(s[j], "<", sizeof(s[j])) == 0
			|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
		{
			if (s[j + 1] == NULL)
			{
				ft_put_str_error("Minishell: erreur ", "de syntaxe près",
					" du symbole inattendu", " « newline »");
				return (ft_free_double_string(s), 1);
			}
			else if ((s[j + 1] && ft_strchr(s[j + 1], '>'))
				|| (s[j + 1] && ft_strchr(s[j + 1], '<')))
			{
				ft_put_str_error("Minishell: syntax ",
					"error near unexpected token `", s[j + 1], "'");
				return (ft_free_double_string(s), 1);
			}
		}
	}
	return (0);
}
