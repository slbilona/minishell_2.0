/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 22:44:12 by ilona             #+#    #+#             */
/*   Updated: 2023/10/11 22:44:30 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

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
