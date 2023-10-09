/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:45:55 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/09 21:59:07 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

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

void	ft_free_info(t_info *info)
{
	ft_free_double_string(info->env);
	if (info->i_diff_pid == 1)
	{
		free(info->diff_pid);
		info->i_diff_pid = 0;
	}
	close(info->saved_stdin);
	close(info->saved_stdout);
	close(info->saved_stderr);
	free(info);
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
			if (&repo[i] && repo[i].cmd)
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
		ft_free_info(info);
}

/* si j == 0 : initialise pipe_fd
sinn free pipe_fd */
int	**ft_free_pipe(t_info *info, int **pipes_fd)
{
	int	i;

	i = 0;
	while (pipes_fd && i < info->nb_de_pipe)
	{
		if (pipes_fd[i])
			free(pipes_fd[i]);
		i++;
	}
	free(pipes_fd);
	return (NULL);
}

int	**ft_free_prec_pipe(int **pipe_fd, int i)
{
	while (pipe_fd && i >= 0)
	{
		if (pipe_fd[i])
		{
			close(pipe_fd[i][0]);
			close(pipe_fd[i][1]);
		}
		if (pipe_fd[i])
			free(pipe_fd[i]);
		i--;
	}
	if (pipe_fd)
		free(pipe_fd);
	return (NULL);
}
