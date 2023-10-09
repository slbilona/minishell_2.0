/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:08:10 by ilona             #+#    #+#             */
/*   Updated: 2023/10/09 19:33:15 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

// cd dans le OLDPWD
int	ft_cd_tiret(t_struct *repo, void *inf)
{
	char	*oldpwd;
	t_info	*info;

	info = inf;
	oldpwd = my_getenv(info, "OLDPWD");
	if (!oldpwd)
	{
		ft_put_str_error("Minishell: cd: ", "« OLDPWD »", " non", " défini");
		return (1);
	}
	ft_export_pwd(info, 0);
	if (chdir(oldpwd))
	{
		free(oldpwd);
		ft_put_str_error("Minishell: cd: ", strerror(errno), NULL, NULL);
		return (1);
	}
	free(oldpwd);
	ft_pwd(repo, inf);
	return (0);
}

// cd dans HOME
int	ft_cd_vague(t_info *info)
{
	char	*home;

	home = my_getenv(info, "HOME");
	if (!home)
	{
		ft_put_str_error("Minishell: ", "cd: ", "« HOME » ", "non défini");
		return (1);
	}
	ft_export_pwd(info, 0);
	if (chdir(home))
	{
		free(home);
		ft_put_str_error("Minishell: cd: ", strerror(errno), NULL, NULL);
		return (1);
	}
	free(home);
	return (0);
}

int	ft_cd_simple(t_info *info, t_struct *repo)
{
	if (access(repo->args[1], F_OK) != 0)
	{
		ft_put_str_error("Minishell: cd: ", repo->args[1],
			": Aucun fichier ou dossier de ce type", NULL);
		return (1);
	}
	if (!ft_directory_ou_non(repo->args[1]))
	{
		ft_put_str_error("Minishell: cd: ", repo->args[1],
			": N'est pas", " un dossier");
		return (1);
	}
	ft_export_pwd(info, 0);
	if (chdir(repo->args[1]))
	{
		ft_put_str_error("Minishell: cd: ", strerror(errno), NULL, NULL);
		return (1);
	}
	return (0);
}

// n'affiche pas de msg d'erreur lorque on essaye d'entrer dans un fichier
int	ft_cd(t_struct *repo, void *inf)
{
	t_info	*info;

	info = inf;
	if (ft_count_double_string(repo[info->i].args) > 2)
	{
		ft_put_str_error("Minishell: cd: trop d'arguments", NULL, NULL, NULL);
		return (1);
	}
	if (repo[info->i].args[1] && ft_strncmp(repo[info->i].args[1],
			"-", sizeof(repo[info->i].args[1])) == 0)
	{
		if (ft_cd_tiret(&repo[info->i], inf))
			return (1);
	}
	else if (!repo[info->i].args[1] || ft_strncmp(repo[info->i].args[1],
			"~", sizeof(repo[info->i].args[1])) == 0)
	{
		if (ft_cd_vague(info))
			return (1);
	}
	else if (repo[info->i].args[1])
		if (ft_cd_simple(info, &repo[info->i]))
			return (1);
	ft_export_pwd(info, 1);
	return (0);
}
