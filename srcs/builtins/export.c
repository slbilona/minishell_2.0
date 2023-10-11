/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:33:49 by ilona             #+#    #+#             */
/*   Updated: 2023/10/11 21:33:50 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

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

void	ft_export_suite(t_struct *repo, t_info *info, int j, int *ret)
{
	int	o;

	o = ft_trouve_egal(repo->args[j]);
	if (o > 0)
	{
		if (!ft_cherche_dans_env(repo->args[j], info, o))
			info->env = mange(info->env, repo->args[j], 0);
	}
	else if (o == -1)
	{
		ft_put_str_error("Minishell: export: `", repo->args[j],
			"': not a", " valid identifier");
		*ret = 1;
	}
}

int	ft_export(t_struct *repo, void *inf)
{
	int		j;
	int		i;
	int		ret;
	t_info	*info;

	j = 1;
	ret = 0;
	info = inf;
	i = info->i;
	if (ft_count_double_string(repo[i].args) < 2)
		return (ft_export_sans_arguments(info));
	while (repo[i].args && repo[i].args[j])
	{
		ft_export_suite(&repo[i], info, j, &ret);
		j++;
	}
	return (ret);
}
