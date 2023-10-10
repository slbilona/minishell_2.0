/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:17:19 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/10 17:55:13 by ilselbon         ###   ########.fr       */
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

	j = 1;
	info = inf;
	o = info->i;
	while (repo[o].args && repo[o].args[j])
	{
		var = ft_strjoin(repo[o].args[j], "=");
		i = 0;
		while (info->env && info->env[i])
		{
			if (ft_strnstr(info->env[i], var, ft_strlen(var)))
			{
				info->env = ft_supprime_sous_chaine(info->env, i);
				break ;
			}
			else
				i++;
		}
		free(var);
		j++;
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

int	ft_export_sans_arguments(t_info *info)
{
	int	i;

	i = 0;
	while (info->env && info->env[i])
	{
		if (write(1, info->env[i], ft_strlen(info->env[i])) == -1)
			return (perror("Minishell: export: erreur d'écriture "), 1);
		if (write(1, "\n", 1) == -1)
			return (perror("Minishell: export: erreur d'écriture "), 1);
		i++;
	}
	return (0);
}

int	ft_export(t_struct *repo, void *inf)
{
	int		j;
	int		o;
	int		i;
	int		ret;
	t_info	*info;

	j = 1;
	o = 0;
	ret = 0;
	info = inf;
	i = info->i;
	if (ft_count_double_string(repo[i].args) < 2)
		return (ft_export_sans_arguments(info));
	while (repo[i].args && repo[i].args[j])
	{
		o = ft_trouve_egal(repo[i].args[j]);
		if (!ft_white_spaces(repo[i].args[j]) && o > 0)
		{
			if (!ft_cherche_dans_env(repo[i].args[j], info, o))
				info->env = mange(info->env, repo[i].args[j], 0);
		}
		else if (o == -1)
		{
			ft_put_str_error("Minishell: export: `", repo[i].args[j],
				"': not a", " valid identifier");
			ret = 1;
		}
		j++;
	}
	return (ret);
}

int ft_builtins_pipe(t_struct *repo, t_info *info, int **pipes_fd)
{
	int	j;
	int	i;
	int	redir;

	j = 0;
	i = info->i;
	redir = 0;
	while (j < 6)
	{
		if (ft_strncmp(repo[i].cmd, info->builtins[j].str,
				ft_strlen(repo[i].cmd)) == 0 && ft_strncmp(repo[i].cmd,
				info->builtins[j].str, ft_strlen(info->builtins[j].str)) == 0)
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
	if (ft_strncmp(repo[i].cmd, info->builtins[j].str,
			ft_strlen(repo[i].cmd)) == 0 && ft_strncmp(repo[i].cmd,
			info->builtins[j].str, ft_strlen(info->builtins[j].str)) == 0)
			ft_exit_pipe(repo, info, pipes_fd);
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
