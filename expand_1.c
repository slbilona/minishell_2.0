/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:08:38 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/11 22:43:47 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_expand_suite(t_info *info, char *str, t_expand *ex)
{
	int	j;

	j = 0;
	if (str[ex->o] == '$' && (ft_quotes(str, ex->o) == 0
			|| ft_quotes(str, ex->o) == 2) && str[ex->o + 1]
		&& str[ex->o + 1] == '?')
		ft_j_et_k_exit(info, &ex->j, &ex->k);
	else if (str[ex->o] == '$' && (ft_quotes(str, ex->o) == 0
			|| ft_quotes(str, ex->o) == 2) && str[ex->o + 1]
		&& (ft_isalnum(str[ex->o + 1]) || str[ex->o + 1] == '_'
			|| ft_quotes(str, ex->o + 1) == 3
			|| ft_quotes(str, ex->o + 1) == 4))
		ft_change_j_et_k(info, &str[ex->o], &ex->j, &ex->k);
	ex->o += 1;
	return (j);
}

int	ft_expand_suite_deux(t_info *info, t_expand *ex, char **str, char **s)
{
	ex->o = 0;
	ex->j = 0;
	ex->k = 0;
	while (str && str[ex->i] && str[ex->i][ex->o])
		ex->j += ft_expand_suite(info, str[ex->i], ex);
	s[ex->i] = ft_cree_dest(info, str[ex->i],
			ft_strlen(str[ex->i]) - ex->j + ex->k, 0);
	if (!s[ex->i])
	{
		ft_free_split(s, ex->i);
		ft_free_double_string(str);
		return (ft_put_str_error("Minishell:", " erreur ",
				"lors de ", "l'expand"), 1);
	}
	return (0);
}

char	**ft_expand(t_info *info, char **str)
{
	char		**s;
	t_expand	*ex;

	ex = info->ex;
	ex->i = 0;
	if (str)
	{
		s = malloc(sizeof(char *) * (ft_count_double_string(str) + 1));
		if (!s)
			return (ft_free_double_string(str), NULL);
		while (str && str[ex->i])
		{
			if (ft_ex_verif_dollar(str[ex->i]))
			{
				if (ft_expand_suite_deux(info, ex, str, s))
					return (NULL);
			}
			else
				s[ex->i] = ft_strdup(str[ex->i]);
			ex->i++;
		}
		s[ex->i] = NULL;
		return (ft_free_double_string(str), s);
	}
	return (NULL);
}
