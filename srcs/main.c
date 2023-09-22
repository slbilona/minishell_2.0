/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/09/22 16:38:28 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_putstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
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

t_info	*ft_init_info(char **env)
{
	t_info	*info;
	
	info = malloc(sizeof(t_info));
	if (!info)
		return (printf("Erreur de la creation de la structure info\n"), NULL);
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
	info->saved_stderr = dup(STDERR_FILENO);
	info->env = ft_cp_env(env);
	if (!info->env)
	{
		printf("Erreur lors de la copie de l'environement\n");
		ft_free_struct(NULL, info, 1);
		return (NULL);
	}
	return (info);
}

int	main(int ac, char **av, char **env)
{
	char		*entree;
	char		**str;
	t_info		*info;
	t_struct	*repo;

	(void) av;
	if (ac == 1)
	{
		info = ft_init_info(env); //initialise la structure info
		if (!info)
			return (1);
		ft_init_builtins(info);
		while (1)
		{
			entree = readline("Minishell$ ");
			if (ft_strlen(entree) > 0)
				add_history(entree);
			//parsing
			if (!main_parsing(entree))
			{
				entree = ft_pre_parsing(entree);
				if (!entree)
					return (1);
				str = ft_new_split(entree, "|");
				if (str)
				{
					repo = ft_init_struct(str); //renvoie le tableau de structure
					if(repo)
					{
						info->nb_de_cmd = ft_count_double_string(str);//pareil je te laisserai le mettre autre part si besoin
						info->nb_de_pipe = info->nb_de_cmd - 1;
						free(entree);
						ft_free_double_string(str);
						//ft_print_repo(repo, info);
						//execution
						ft_execution_coordinateur(repo, info);			
					}
					else
						ft_free_double_string(str);
				}
				else
					free(entree);
			}
			else
				free(entree);
		}
		get_next_line(-1);
		ft_free_struct(NULL, info, 1);//free la structure info
	}
	else
	{
		entree = ft_pre_parsing(ft_strdup(av[1]));
		str = ft_new_split(entree, NULL);
		int i = 0;
		printf("--------------------------------\n");
		printf("entree : \'%s\'\n", entree);
		while (str[i])
		{
			printf("\'%s\'\n", str[i]);
			i++;
		}
		printf("--------------------------------\n");
		ft_free_double_string(str);
		free(entree);
	}
	return (0);
}
