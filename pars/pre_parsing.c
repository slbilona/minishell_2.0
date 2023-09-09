/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:39:35 by ilona             #+#    #+#             */
/*   Updated: 2023/09/09 23:44:49 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	*ft_pre_parsing(char *entree)
{
	char	*n_entree;

	n_entree = ft_ajoute_espace(entree);
	if (!n_entree)
		return (NULL);
	return (n_entree);
}
