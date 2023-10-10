/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:17:29 by ilona             #+#    #+#             */
/*   Updated: 2023/10/10 20:54:48 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	parsing_exec(t_info *info, char *entree)
{
	char		**str;
	t_struct	*repo;

	add_history(entree);
	if (main_parsing(entree))
		return (free(entree), 1);
	entree = ft_ajoute_espace(entree);
	if (!entree)
		return (1);
	str = ft_new_split(entree, "|");
	if (!str)
		return (free(entree), 1);
	// if (ft_expand(info, str))
	// 	return (ft_free_double_string(str), 1);
	//str = ft_expand_test(info, str);
	repo = ft_init_struct(info, str);
	if (!repo)
	{
		return (ft_free_double_string(str), free(entree), 1);
	}
	if (ft_init_info_deux(info, ft_count_double_string(str)))
		return (1);
	free(entree);
	ft_free_double_string(str);
	ft_execution_coordinateur(repo, info);
	return (0);
}
