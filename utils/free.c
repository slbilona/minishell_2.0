/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:55 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/03 16:57:13 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	ft_free_double_string(char **str)
{
	int	j;

	j = 0;
	if (str)
	{
		while (str[j])
		{
			if (str[j])
				free(str[j]);
			j++;
		}
		free(str);
	}
}

/* si j == 0 free la structure repo 
si j == 1 free la structure info
si j == 2 free les deux */
void	ft_free_struct(t_struct *repo, t_info *info, int j)
{
	int	i;

	if (repo && (j == 0 || j == 2))
	{
		i = 0;
		while (i < info->nb_de_cmd)
		{
			if (repo[i].cmd)
				free(repo[i].cmd);
			if (repo[i].path)
				free(repo[i].path);
			ft_free_double_string(repo[i].args);
			ft_free_double_string(repo[i].redirection);
			i++;
		}
		free(repo);
	}
	if (info && (j == 1 || j == 2))
	{
		ft_free_double_string(info->env);
		i = 0;
		if (info->diff_pid)
			free(info->diff_pid);
		close(info->saved_stdin);
		close(info->saved_stdout);
		close(info->saved_stderr);
		free(info);
	}
}

/* si j == 0 : initialise pipe_fd
sinn free pipe_fd */
int	**ft_init_free_pipe(t_info *info, int j, int **pipes_fd)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	if (!j)
	{
		pipe_fd = malloc(sizeof(int *) * info->nb_de_pipe);
		while (i < info->nb_de_pipe)
		{
			pipe_fd[i] = malloc(sizeof(int) * 2);
			// Verifier si l'allocation n'a pas echoue
			if (pipe(pipe_fd[i]) == -1)
			{
				perror("Erreur lors de la création des tubes");
				return (NULL);
			}
			i++;
		}
		return (pipe_fd);
	}
	else
	{
		while (i < info->nb_de_pipe)
			free(pipes_fd[i++]);
		free(pipes_fd);
		return (NULL);
	}
	return (NULL);
}