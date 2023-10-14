/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:08:38 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/14 17:59:52 by ilselbon         ###   ########.fr       */
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
			|| str[ex->o + 1] == '!' || ft_quotes(str, ex->o + 1) == 3
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
	ex->i = -1;
	if (str)
	{
		s = malloc(sizeof(char *) * (ft_count_double_string(str) + 1));
		if (!s)
			return (ft_free_double_string(str), NULL);
		while (str && str[++ex->i])
		{
			if (!(ex->i > 0 && ft_strncmp(str[ex->i - 1],
						"<<", 3) == 0) && ft_ex_verif_dollar(str[ex->i]))
			{
				if (ft_expand_suite_deux(info, ex, str, s))
					return (NULL);
			}
			else
				s[ex->i] = ft_strdup(str[ex->i]);
		}
		s[ex->i] = NULL;
		return (ft_free_double_string(str), s);
	}
	return (NULL);
}

char	**ft_rafistole(char **s, char **strg, int j)
{
	int		i;
	int		o;
	int		k;
	char	**str;

	o = 0;
	i = 0;
	if (!strg)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_count_double_string(s)
				+ ft_count_double_string(strg) + 1));
	while (i < j && s[i])
		str[o++] = ft_strdup(s[i++]);
	k = -1;
	while (strg[++k])
		str[o++] = ft_strdup(strg[k]);
	i++;
	while (s[i])
		str[o++] = ft_strdup(s[i++]);
	str[o] = NULL;
	ft_free_double_string(s);
	return (str);
}

char	**ft_expand_etc(t_info *info, char **str)
{
	int		i;
	char	**s;
	char	**strg;

	i = 0;
	s = ft_expand(info, str);
	if (!s)
		return (NULL);
	while (s && s[i])
	{
		if (ft_white_space_2(s[i]))
		{
			strg = ft_new_split(s[i], NULL);
			if (!strg)
			{
				ft_free_double_string(s);
				return (NULL);
			}
			s = ft_rafistole(s, strg, i);
			ft_free_double_string(strg);
		}
		i++;
	}
	return (s);
}
