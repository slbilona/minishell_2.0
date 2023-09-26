/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:40:25 by ilona             #+#    #+#             */
/*   Updated: 2023/09/26 16:04:00 by ilona            ###   ########.fr       */
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
		return (ft_put_str_error("Erreur de la creation de la structure info", NULL, NULL, NULL), NULL);
	info->fork = 0;
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
	info->saved_stderr = dup(STDERR_FILENO);
	info->env = ft_cp_env(env);
	ft_init_builtins(info);
	if (!info->env)
	{
		ft_put_str_error("Erreur lors de la copie de l'environement", NULL, NULL, NULL);
		ft_free_struct(NULL, info, 1);
		return (NULL);
	}
	return (info);
}

int ft_init_info_deux(t_info *info, int i)
{
	info->nb_de_cmd = i;
	info->nb_de_pipe = info->nb_de_cmd - 1;
	info->diff_pid = malloc(sizeof(pid_t) * info->nb_de_cmd);
	if (!info->diff_pid)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*entree;
	// char		**str;
	t_info		*info;
	// t_struct	*repo;

	(void) av;
	if (ac == 1)
	{
		info = ft_init_info(env); //initialise la structure info
		if (!info)
			return (1);
		while (1)
		{
			entree = readline("Minishell$ ");
			if (ft_strlen(entree) > 0)
				add_history(entree);
			//parsing
			if (!main_parsing(entree))
			{
				entree = ft_pre_parsing(entree);
				printf("entree : %s\n", entree);
				if (!entree)
					return (1);
				free(entree);
			}
			// 	str = ft_new_split(entree, "|");
			// 	if (str)
			// 	{
			// 		repo = ft_init_struct(str); //renvoie le tableau de structure
			// 		if(repo)
			// 		{
			// 			ft_init_info_deux(info, ft_count_double_string(str));
			// 			free(entree);
			// 			ft_free_double_string(str);
			// 			//execution
			// 			ft_execution_coordinateur(repo, info);
			// 		}
			// 		else
			// 			ft_free_double_string(str);
			// 	}
			// 	else
			// 		free(entree);
			// }
			// else
			// 	free(entree);
		}
		get_next_line(-1);
		ft_free_struct(NULL, info, 1);//free la structure info
	}
	return (0);
}
	