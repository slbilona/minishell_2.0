/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/09/09 22:40:32 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	main(void)
{
	char	*entree;

	while (1)
	{
		entree = readline("Minishell$ ");
		add_history(entree);
		entree = ft_pre_parsing(entree);
	// 	if (ft_pre_parsing(entree))
	// 		return (1);
	// 	str = ft_split(entree, '|');
	// 	ft_init_struct(str);
		free(entree);
	}
	return (0);
}
