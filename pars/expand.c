/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:08:38 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/03 20:05:52 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// verifie si il y a un dollar suivi d'un caractere visible
int	ft_ex_verif_dollar(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strrchr(line, '$');
	while (str && str[0] != line[i])
		i++;
	if (str && (ft_quotes(line, i) == 0
			|| ft_quotes(line, i) == 2) && str[1]
		&& (str[1] < 9 || 13 < str[1]) && str[1] != 32)
		return (1);
	return (0);
}

void	ft_j_et_k_exit(t_info *info, int *j, int *k)
{
	char *str;

	str = ft_itoa(info->exit);
	*j += 2;
	*k += ft_strlen(str);
	free(str);
}

void	ft_expand(t_info *info, char **str)
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
			{
				if (str[i][o] == '$' && (ft_quotes(str[i], o) == 0
					|| ft_quotes(str[i], o) == 2) && str[i][o + 1] && str[i][o + 1] == '?')
				{
					ft_j_et_k_exit(info, &j, &k);
				}
				else if (str[i][o] == '$' && (ft_quotes(str[i], o) == 0
					|| ft_quotes(str[i], o) == 2) && str[i][o + 1]
					&& (ft_isalnum(str[i][o + 1]) || str[i][o + 1] == '_'))
					ft_change_j_et_k(info, &str[i][o], &j, &k);
				o++;
			}
			str[i] = ft_cree_dest(info, str[i], ft_strlen(str[i]) - j + k, 1);
			// Verifier la string
		}
		i++;
	}
}
