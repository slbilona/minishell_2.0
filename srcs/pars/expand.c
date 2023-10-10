/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:08:38 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/10 23:35:14 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_expand_suite(t_info *info, char *str, int *o, int *k)
{
	int	j;

	j = 0;
	if (str[*o] == '$' && (ft_quotes(str, *o) == 0
			|| ft_quotes(str, *o) == 2) && str[*o + 1]
		&& str[*o + 1] == '?')
		ft_j_et_k_exit(info, &j, k);
	else if (str[*o] == '$' && (ft_quotes(str, *o) == 0
			|| ft_quotes(str, *o) == 2) && str[*o + 1]
		&& (ft_isalnum(str[*o + 1]) || str[*o + 1] == '_'
			|| ft_quotes(str, *o + 1) == 3
			|| ft_quotes(str, *o + 1) == 4))
		ft_change_j_et_k(info, &str[*o], &j, k);
	*o += 1;
	return (j);
}

char	**ft_expand(t_info *info, char **str)
{
	int		i;
	int		o;
	int		j;
	int		k;
	char	**s;

	i = 0;
	k = 0;
	if (str)
	{
		s = malloc(sizeof(char *) * (ft_count_double_string(str) + 1));
		if (!s)
			return (ft_free_double_string(str), NULL);
		while (str && str[i])
		{
			o = 0;
			j = 0;
			if (ft_ex_verif_dollar(str[i]))
			{
				while (str && str[i] && str[i][o])
					j += ft_expand_suite(info, str[i], &o, &k);
				s[i] = ft_cree_dest(info, str[i], ft_strlen(str[i]) - j + k, 0);
				if (!s[i])
				{
					ft_free_split(s, i);
					ft_free_double_string(str);
					return (ft_put_str_error("Minishell:", " erreur ",
							"lors de ", "l'expand"), NULL);
				}
			}
			else
				s[i] = ft_strdup(str[i]);
			i++;
		}
		s[i] = NULL;
		ft_free_double_string(str);
		return (s);
	}
	return (NULL);
}

int	ft_cree_dest_exit(t_info *info, char *dest, int *j)
{
	int		o;
	char	*test;

	o = 0;
	test = ft_itoa(info->exit);
	while (test && test[o])
	{
		dest[*j] = test[o];
		*j += 1;
		o++;
	}
	if (test)
		free(test);
	return (2);
}

int	ft_cree_dest_suite(t_info *info, char *dest, int *j, char *c)
{
	int	o;
	int	l;
	int	k;
	int	ret;

	o = 0;
	ret = 0;
	l = ft_change_j_et_k(info, c, &o, &k);
	ret = o;
	if (l > -1)
	{
		while (info->env && info->env[l] && info->env[l][o])
		{
			dest[*j] = info->env[l][o++];
			*j += 1;
		}
	}
	return (ret);
}

/* Si n == 1 free line
Si n == 0 ne free pas line */
char	*ft_cree_dest(t_info *info, char *s, int k, int n)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (s && s[i])
	{
		if (s[i] == '$' && (ft_quotes(s, i) == 0 || ft_quotes(s, i)
				== 2) && s[i + 1] && s[i + 1] == '?')
			i += ft_cree_dest_exit(info, dest, &j);
		else if (s[i] == '$' && (ft_quotes(s, i) == 0 || ft_quotes(s, i) == 2)
			&& s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'
				|| ft_quotes(s, i + 1) == 3 || ft_quotes(s, i + 1) == 4))
			i += ft_cree_dest_suite(info, dest, &j, &s[i]);
		else if (s[i])
			dest[j++] = s[i++];
	}
	dest[j] = 0;
	if (n)
		free(s);
	return (dest);
}
