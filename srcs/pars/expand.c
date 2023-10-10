/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:08:38 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/10 16:32:25 by ilselbon         ###   ########.fr       */
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

int	ft_expand(t_info *info, char **str)
{
	int	i;
	int	o;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str && str[i])
	{
		o = 0;
		j = 0;
		if (ft_ex_verif_dollar(str[i]))
		{
			while (str && str[i] && str[i][o])
				j += ft_expand_suite(info, str[i], &o, &k);
			str[i] = ft_cree_dest(info, str[i], ft_strlen(str[i]) - j + k, 1);
			if (!str[i])
				return (ft_put_str_error("Minishell:", " erreur ",
						"lors de ", "l'expand"), 1);
		}
		i++;
	}
	return (0);
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

int	ft_cree_dest_suite(t_info *info, char **dest, int *j, char *c)
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
			(*dest)[*j] = info->env[l][o++];
			*j += 1;
		}
	}
	return (ret);
}

/* Si n == 1 free line
Si n == 0 ne free pas line */
char	*ft_cree_dest(t_info *info, char *line, int k, int n)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& line[i + 1] == '?')
			i += ft_cree_dest_exit(info, dest, &j);
		else if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'
				|| ft_quotes(line, i + 1) == 3 || ft_quotes(line, i + 1) == 4))
			i += ft_cree_dest_suite(info, &dest, &j, &line[i]);
		else if (line[i])
			dest[j++] = line[i++];
	}
	dest[j] = 0;
	if (n)
		free(line);
	return (dest);
}
