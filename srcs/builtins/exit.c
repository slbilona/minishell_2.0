/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:59:28 by ilona             #+#    #+#             */
/*   Updated: 2023/10/09 20:50:40 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_exit(t_struct *repo, void *inf)
{
	int				i;
	int				exit_num;
	t_info			*info;
	long long int	num;

	num = 0;
	info = inf;
	i = info->i;
	exit_num = 0;
	if (dup2(info->saved_stdout, STDOUT_FILENO) == -1)
		return (perror("dup2"), 1);
	if (ft_count_double_string(repo[i].args) > 2
		&& !ft_que_des_chiffres(repo[i].args[1]))
	{
		return (ft_put_str_error("Minishell: ", "exit:",
				" too many arguments", NULL), 1);
	}
	ft_put_str_error("exit", NULL, NULL, NULL);
	if (ft_count_double_string(repo[i].args) >= 1)
		ft_exit_suite(&repo[i], info, &num, &exit_num);
	ft_free_struct(repo, info, 2);
	exit(num);
}

int	ft_exit_pipe(t_struct *repo, void *inf, int **pipes_fd)
{
	int				i;
	int				exit_num;
	t_info			*info;
	long long int	num;

	num = 0;
	info = inf;
	i = info->i;
	exit_num = 0;
	if (dup2(info->saved_stdout, STDOUT_FILENO) == -1)
		return (perror("dup2"), 1);
	if (ft_count_double_string(repo[i].args) > 2
		&& !ft_que_des_chiffres(repo[i].args[1]))
	{
		return (ft_put_str_error("Minishell: ", "exit:",
				" too many arguments", NULL), 1);
	}
	if (ft_count_double_string(repo[i].args) >= 1)
		ft_exit_suite(&repo[i], info, &num, &exit_num);
	ft_free_pipe(info, pipes_fd);
	ft_free_struct(repo, info, 2);
	exit(num);
}

void	ft_exit_suite(t_struct *repo, t_info *info,
		long long int *num, int *exit_num)
{
	if (ft_long_atoi(repo->args[1], num)
		|| ft_que_des_chiffres(repo->args[1]) || ft_signes(repo->args[1]))
	{
		ft_put_str_error("Minishell: exit: ", repo->args[1],
			": numeric argument required", NULL);
		*exit_num = 2;
	}
	if (*exit_num)
	{
		ft_free_struct(repo, info, 2);
		exit(*exit_num);
	}
}

int	ft_long_atoi(char *str, long long int *num)
{
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	if (str)
	{
		while (str[i] && ((9 <= str[i] && str[i] <= 13) || str[i] == ' '))
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				signe = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			if (*num > (LLONG_MAX - (str[i] - '0')) / 10)
				return (2);
			*num = *num * 10 + str[i] - 48;
			i++;
		}
	}
	*num = *num * signe;
	return (0);
}
