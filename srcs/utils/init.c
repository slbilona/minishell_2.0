/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:11:35 by ilona             #+#    #+#             */
/*   Updated: 2023/10/11 15:04:08 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	**ft_init_pipe(t_info *info)
{
	int	i;
	int	**pipe_fd;

	i = 0;
	pipe_fd = malloc(sizeof(int *) * info->nb_de_pipe);
	if (!pipe_fd)
		return (NULL);
	while (i < info->nb_de_pipe)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
			return (ft_free_prec_pipe(pipe_fd, i));
		if (pipe(pipe_fd[i]) == -1)
		{
			perror("Minishell: pipe: Erreur lors de la création des tubes");
			ft_free_prec_pipe(pipe_fd, i);
			return (NULL);
		}
		i++;
	}
	return (pipe_fd);
}

void	ft_init_builtins(t_info *info)
{
	info->builtins[0].ptr = (void *)ft_export;
	info->builtins[1].ptr = (void *)ft_echo;
	info->builtins[2].ptr = (void *)ft_cd;
	info->builtins[3].ptr = (void *)ft_pwd;
	info->builtins[4].ptr = (void *)ft_env;
	info->builtins[5].ptr = (void *)ft_unset;
	info->builtins[6].ptr = (void *)ft_exit;
	info->builtins[0].str = "export";
	info->builtins[1].str = "echo";
	info->builtins[2].str = "cd";
	info->builtins[3].str = "pwd";
	info->builtins[4].str = "env";
	info->builtins[5].str = "unset";
	info->builtins[6].str = "exit";
}

t_info	*ft_init_info(char **env)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_put_str_error("Erreur de la creation de la structure info",
				NULL, NULL, NULL), NULL);
	info->i_diff_pid = 0;
	info->exit = 0;
	info->saved_stdin = dup(STDIN_FILENO);
	info->saved_stdout = dup(STDOUT_FILENO);
	info->saved_stderr = dup(STDERR_FILENO);
	info->env = ft_cp_env(env);
	ft_init_builtins(info);
	if (!info->env)
	{
		ft_put_str_error("Erreur lors", " de la copie ",
			"de l'environement", NULL);
		ft_free_struct(NULL, info, 1);
		return (NULL);
	}
	return (info);
}

int	ft_init_info_deux(t_info *info, int i)
{
	info->fork = 0;
	info->i_heredoc = 0;
	info->nb_de_cmd = i;
	info->nb_de_pipe = info->nb_de_cmd - 1;
	info->diff_pid = malloc(sizeof(pid_t) * info->nb_de_cmd);
	if (!info->diff_pid)
	{
		ft_put_str_error("Minishell:", " erreur lors de ",
			"l'initialisation de la", " structure info");
		return (1);
	}
	info->i_diff_pid = 1;
	return (0);
}

void	ft_init_sep(char *sep)
{
	sep[0] = 9;
	sep[1] = 10;
	sep[2] = 11;
	sep[3] = 12;
	sep[4] = 13;
	sep[5] = 32;
	sep[6] = 0;
}
