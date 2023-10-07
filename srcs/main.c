/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/10/07 14:26:07 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_putstr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		printf("%s, ", str[i]);
		//write(1, str[i], sizeof(str[i]));
		i++;
	}
	printf("\n");
}

//print le tableau de structure entier
void	ft_print_repo(t_struct *repo, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->nb_de_cmd)
	{
		printf("----------------------------------------------\n");
		printf("repo[%d] :\ncmd : %s\n", i, repo[i].cmd);
		if (repo[i].args)
		{
			j = 0;
			while (repo[i].args[j])
			{
				printf("args[%d] : %s\n", j, repo[i].args[j]);
				j++;
			}
		}
		if (repo[i].redirection)
		{
			j = 0;
			while (repo[i].redirection[j])
			{
				printf("redirection[%d] : %s\n", j, repo[i].redirection[j]);
				j++;
			}
		}
		printf("----------------------------------------------\n");
		printf("\n\n");
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*entree;
	char		**str;
	t_info		*info;
	t_struct	*repo;
	int			i;

	i = 0;
	(void) av;
	
	if (ac == 1)
	{
		info = ft_init_info(env); //initialise la structure info
		if (!info)
			return (1);
		while (1)
		{
			if (i % 2)
				entree = readline("🌺 \x1b[35mMinishell$ \x1b[0m");
			else
				entree = readline("🐙 \x1b[31mMinishell$ \x1b[0m");
			if (ft_strlen(entree) > 0)
			{
				add_history(entree);
				//parsing
				if (!main_parsing(entree))
				{
					entree = ft_pre_parsing(entree);
					if (entree)
					{
						str = ft_new_split(entree, "|");
						if (str)
						{
							repo = ft_init_struct(info, str); //renvoie le tableau de structure
							if (repo)
							{
								ft_init_info_deux(info, ft_count_double_string(str));
								// verifier si la fonction au dessus n'échoue pas
								free(entree);
								ft_free_double_string(str);
								//execution
								ft_execution_coordinateur(repo, info);
							}
							else
							{
								info->exit = 2;
								ft_free_double_string(str);
								free(entree);
							}
						}
						else
						{
							info->exit = 2;
							free(entree);
						}
					}
					else
					{
						info->exit = 2;
						free(entree);
					}
				}
				else
				{
					info->exit = 2;
					free(entree);
				}
			}
			else
				free(entree);
			i++;
		}
		ft_free_struct(NULL, info, 1); //free la structure info
	}
	return (0);
}
	