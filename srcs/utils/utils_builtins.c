/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:11:47 by ilona             #+#    #+#             */
/*   Updated: 2023/10/10 14:14:19 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

// return 1 si il y a un white space dans la chaine
int	ft_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

/* cherche une variable dans l'environnement,
la remplace par sa nouvelle valeur si elle existe deja et return 1
sinn elle return 0 */
int	ft_cherche_dans_env(char *str, t_info *info, int o)
{
	int	i;

	i = 0;
	while (info->env && info->env[i])
	{
		if (!ft_strncmp(info->env[i], str, o + 1))
		{
			free(info->env[i]);
			info->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_trouve_egal(char *str)
{
	int	i;

	if (str && !ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	i = 1;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		else if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
	}
	return (-2);
}

// Copie une double string dans une nouvelle et la retourne
char	**ft_cp_env(char **ancien_env)
{
	int		i;
	char	**env;

	i = 0;
	env = malloc(sizeof(char *) * (ft_count_double_string(ancien_env) + 1));
	while (ancien_env[i])
	{
		env[i] = ft_strdup(ancien_env[i]);
		if (!env)
		{
			ft_free_split(env, i);
			return (NULL);
		}
		i++;
	}
	env[ft_count_double_string(ancien_env)] = NULL;
	return (env);
}
