/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:50:46 by ilselbon          #+#    #+#             */
/*   Updated: 2023/09/19 20:04:58 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// ne fonctionne pqs lorsqu'on qppelle la fonction env
void	ft_unset(t_struct *repo, void *inf)
{
	int		i;
	int		j;
	char	*var;
	t_info	*info;

	j = 1;
	info = inf;
	while (repo->args[j])
	{
		var = ft_strjoin(repo->args[j], "=");
		i = 0;
		while (info->env[i])
		{
			if (ft_strnstr(info->env[i], var, ft_strlen(var)))
			{
				info->env = ft_supprime_sous_chaine(info->env, i);
				//gerer le cas ou info->env est NULL
				break ;
			}
			else
				i++;
		}
		free(var);
		j++;
	}
}

void	ft_env(t_struct *repo, void *inf)
{
	int		i;
	t_info	*info;

	i = 0;
	info = inf;
	(void) repo;
	while (info->env[i])
	{
		printf("%s\n", info->env[i]);
		i++;
	}
}

int	ft_trouve_egal(char *str)
{
	int i;

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

int	ft_cherche_dans_env(char *str, t_info *info, int o)
{
	int i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], str, o + 1))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(t_struct *repo, void *inf)
{
	int		j;
	int		o;
	//char	*var;
	t_info	*info;

	j = 1;
	o = 0;
	info = inf;
	while (repo->args[j])
	{
		o = ft_trouve_egal(repo->args[j]);
		if (!ft_white_spaces(repo->args[j]) && o > 0)
		{
			if(ft_cherche_dans_env(repo->args[j], info, o))
			{
				printf("trouve\n");
				//remplacer l'ancienne chaine par la nouvelle
			}
			else
			{
				printf("pas trouve\n");
				//info->env = mange(info->env, repo->args[j], 0);
				//verifier si il n'y a pas une erreur;
			}
		}
		else if (o == -1)
		{
			dup2(info->saved_stderr, STDERR_FILENO);
			printf("Minishell: export: `%s': not a valid identifier\n", repo->args[j]);
		}
		j++;
	}
	printf("rien a faire\n");
}
