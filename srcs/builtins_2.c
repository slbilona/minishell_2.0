/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:50:46 by ilselbon          #+#    #+#             */
/*   Updated: 2023/09/19 17:45:36 by ilselbon         ###   ########.fr       */
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

	i = 0;
	j = 1;
	info = inf;
	while (repo->args[j])
	{
		var = ft_strjoin(repo->args[j], "=");
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

void	ft_export(t_struct *repo, void *inf)
{
	int		i;
	int		j;
	t_info	*info;

	i = 0;
	j = 1;
	info = inf;
	while (repo->args[j])
	{
		if (ft_strchr(repo->args[j] + 1, '=') && !ft_white_spaces(repo->args[j]))
			info->env = mange(info->env, repo->args[j], 0);
		else if (ft_strchr(repo->args[j], '=') || ft_white_spaces(repo->args[j]))
		{
			dup2(info->saved_stderr, STDERR_FILENO);
			printf("Minishell: export: `%s': not a valid identifier\n", repo->args[j]);
		}
		j++;
	}
}
