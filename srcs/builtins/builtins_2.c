/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:17:19 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/11 22:12:27 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_unset(t_struct *repo, void *inf)
{
	int		i;
	int		j;
	int		o;
	char	*var;
	t_info	*info;

	j = 0;
	info = inf;
	o = info->i;
	while (repo[o].args && repo[o].args[++j])
	{
		var = ft_strjoin(repo[o].args[j], "=");
		i = -1;
		while (info->env && info->env[++i])
		{
			if (ft_strnstr(info->env[i], var, ft_strlen(var)))
			{
				info->env = ft_supprime_sous_chaine(info->env, i);
				break ;
			}
		}
		free(var);
	}
	return (0);
}

int	ft_env(t_struct *repo, void *inf)
{
	int		i;
	t_info	*info;

	i = 0;
	info = inf;
	(void) repo;
	while (info->env && info->env[i])
	{
		if (write(1, info->env[i], ft_strlen(info->env[i])) == -1)
			return (perror("Minishell: env: erreur d'écriture "), 1);
		if (write(1, "\n", 1) == -1)
			return (perror("Minishell: env: erreur d'écriture "), 1);
		i++;
	}
	return (0);
}

int	ft_builtins_pipe(t_struct *repo, t_info *info)
{
	int	j;
	int	i;

	j = 0;
	i = info->i;
	while (j < 6)
	{
		if (ft_strncmp(repo[i].cmd, info->builtins[j].str,
				ft_strlen(repo[i].cmd)) == 0 && ft_strncmp(repo[i].cmd,
				info->builtins[j].str, ft_strlen(info->builtins[j].str)) == 0)
		{
			repo[i].ret = info->builtins[j].ptr(repo, info);
			return (0);
		}
		j++;
	}
	if (ft_strncmp(repo[i].cmd, info->builtins[j].str,
			ft_strlen(repo[i].cmd)) == 0 && ft_strncmp(repo[i].cmd,
			info->builtins[j].str, ft_strlen(info->builtins[j].str)) == 0)
		ft_exit_pipe(repo, info);
	return (1);
}

int	ft_builtins(t_struct *repo, t_info *info)
{
	int	j;
	int	i;
	int	redir;

	j = 0;
	i = info->i;
	redir = 0;
	while (j < 7)
	{
		if (ft_strncmp(repo[i].cmd, info->builtins[j].str,
				ft_strlen(repo[i].cmd)) == 0
			&& ft_strncmp(repo[i].cmd, info->builtins[j].str,
				ft_strlen(info->builtins[j].str)) == 0)
		{
			if (repo[i].redirection)
				redir = ft_redirection(repo[i].redirection);
			if (!redir)
				repo[i].ret = info->builtins[j].ptr(repo, info);
			else
				repo[i].ret = redir;
			return (repo[i].ret);
		}
		j++;
	}
	return (1);
}
