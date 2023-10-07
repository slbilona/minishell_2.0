/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:08:38 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/07 13:54:58 by ilona            ###   ########.fr       */
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
					&& (ft_isalnum(str[i][o + 1]) || str[i][o + 1] == '_' || ft_quotes(str[i], o + 1) == 3 || ft_quotes(str[i], o + 1) == 4))
					ft_change_j_et_k(info, &str[i][o], &j, &k);
				o++;
			}
			str[i] = ft_cree_dest(info, str[i], ft_strlen(str[i]) - j + k, 1);
			// Verifier la string
		}
		i++;
	}
}

// verifie si il y a un dollar suivi d'un caractere visible
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

/* genre de strjoin pour creer ma variable suivie d'un '='
si o == 1 copie str[i + 1]
si o == 0 copie str[i]*/
char	*ft_cree_var(int j, char *str, int o)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * (j + 1));
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
	printf("var : %s, str : %s\n", var, str);
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

/* Si n == 1 free line
Si n == 0 ne free pas line */
char	*ft_cree_dest(t_info *info, char *line, int k, int n)
{
	int		i; // parcours line
	int		j; // parcours dest
	int		o;
	int		l; // parcours l'env
	char	*dest;
	char	*test;
	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&&  line[i + 1] == '?')
		{
			test = ft_itoa(info->exit);
			o = 0;
			while (test && test[o])
				dest[j++] = test[o++];
			i += 2;
			free(test);
		}
		else if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_' || ft_quotes(line, i+1) == 3 || ft_quotes(line, i+1) == 4))
		{
			o = 0;
			l = ft_change_j_et_k(info, &line[i], &o, &k);
			i += o;
			if (l > -1)
			{
				while (info->env && info->env[l] && info->env[l][o])
					dest[j++] = info->env[l][o++];
			}
		}
		else if (line[i])
			dest[j++] = line[i++];
	}
	dest[j] = 0;
	if (n)
		free(line);
	return (dest);
}
