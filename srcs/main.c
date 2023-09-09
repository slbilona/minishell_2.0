/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/09/10 00:03:28 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(1,&str[i],1);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	char	*entree;
	char	**str;

	while (1)
	{
		entree = readline("Minishell$ ");
		add_history(entree);
		entree = ft_pre_parsing(entree);
		if (!entree)
			return (1);
		str = ft_split(entree, '|');
		ft_init_struct(str);
		free(entree);
	}
	return (0);
}
