/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:02:41 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/10 16:17:23 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_redirection(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (ft_strncmp("> ", str[i], 2) == 0)
		{
			if (ft_redirection_output(str, i))
				return (1);
		}
		else if (ft_strncmp(">> ", str[i], 3) == 0)
		{
			if (ft_redirection_output_append(str, i))
				return (1);
		}
		else if (ft_strncmp("< ", str[i], 2) == 0)
		{
			if (ft_redirection_input(str, i))
				return (1);
		}
		else if (ft_strncmp("<< ", str[i], 3) == 0)
			if (ft_lecture_heredoc())
				return (1);
	}
	return (0);
}

int	ft_redirection_input(char **str, int i)
{
	int	fd;

	fd = open(str[i] + 2, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_redirection_output(char **str, int i)
{
	int	fd;

	fd = open(str[i] + 2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_put_str_error("Minishell: ", str[i] + 2, ": ", strerror(errno));
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_redirection_output_append(char **str, int i)
{
	int	fd;

	fd = open(str[i] + 3, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("erno : %d\n", errno);
		ft_put_str_error("Minishell: ", str[i] + 3, ": ", strerror(errno));
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_put_str_error("Minishell: ", str[i] + 3, ": ", strerror(errno));
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
