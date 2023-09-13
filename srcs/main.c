/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/09/13 18:51:40 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	printf("\n");
}

//print le tableau de structure entier
void ft_print_repo(t_struct *repo, t_info *info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < info->nb_de_cmd)
	{
		printf("repo[%d] :\ncmd : %s\n", i, repo[i].cmd);
		if (repo[i].args)
		{
			j = 0;
			while(repo[i].args[j])
			{
				printf("args[%d] : %s\n", j, repo[i].args[j]);
				j++;
			}
		}
		if(repo[i].redirection)
		{
			j = 0;
			while(repo[i].redirection[j])
			{
				printf("redirection[%d] : %s\n", j, repo[i].redirection[j]);
				j++;
			}
		}
		printf("\n\n");
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*entree;
	char	**str;
	t_struct *repo;
	t_info	*info;
	int i;
	(void) av;

	i = 0;
	if (ac == 1)
	{
		info = malloc(sizeof(t_info)); //j'ai mis ca la mais je te laisserais le mettre dans une fonction speciale qui initialise la structure info etc
		info->env = env;
		while (1)
		{
			entree = readline("Minishell$ ");
			add_history(entree);
			//parsing
			main_parsing(entree);
			entree = ft_pre_parsing(entree);
			if (!entree)
				return (1);
			str = ft_split(entree, '|');
			repo = ft_init_struct(str); //renvoie le tableau de structure
			info->nb_de_cmd = ft_count_cmd(str);//pareil je te laisserai le mettre autre part si besoin
			free(entree);
			ft_free_double_string(str);
			//ft_print_repo(repo, info);
			//execution
			ft_execution(repo, info);
			ft_free_struct(repo, info, 0);//free la structure repo
			i++;
		}
		ft_free_struct(repo, info, 1);//free la structure info
	}
	return (0);
}
