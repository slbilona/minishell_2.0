/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 23:49:53 by ilona             #+#    #+#             */
/*   Updated: 2023/10/10 23:24:11 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

// verifie si il y a un dollar suivi d'un caractere visible
int	ft_ex_verif_dollar(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && (ft_quotes(str, i) == 0
				|| ft_quotes(str, i) == 2) && str[i + 1]
			&& !ft_white_space_char(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_j_et_k_exit(t_info *info, int *j, int *k)
{
	char	*str;

	str = ft_itoa(info->exit);
	*j += 2;
	*k += ft_strlen(str);
	free(str);
}

// Vérifie si il y a un dollar suivi d'un caractere visible
int	ft_verif_dollar(char *line)
{
	char	*str;

	str = ft_strrchr(line, '$');
	if (str && str[1] && (str[1] < 9 || 13 < str[1]) && str[1] != 32)
	{
		return (1);
	}
	return (0);
}

/* j */
int	ft_change_j_et_k(t_info *info, char *str, int *j, int *k)
{
	int		i;
	char	*var;

	i = 1;
	*j += 1;
	while (str && str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		*j += 1;
	}
	var = ft_cree_var(i, str, 1);
	i = 0;
	while (info->env && info->env[i])
	{
		if (ft_strncmp(var, info->env[i], ft_strlen(var)) == 0)
		{
			*k += ft_strlen(info->env[i]) - ft_strlen(var);
			free(var);
			return (i);
		}
		i++;
	}
	free(var);
	return (-1);
}

/* genre de strjoin pour creer ma variable suivie d'un '='
si o == 1 copie str[i + 1]
si o == 0 copie str[i]*/
char	*ft_cree_var(int j, char *str, int o)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * (j + 1));
	if (!var)
		return (NULL);
	while (i < j - 1)
	{
		if (o)
			var[i] = str[i + 1];
		else
			var[i] = str[i];
		i++;
	}
	var[i] = '=';
	var[i + 1] = 0;
	return (var);
}
