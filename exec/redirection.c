/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:32:48 by ilona             #+#    #+#             */
/*   Updated: 2023/09/20 20:51:50 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// pb lorsque je reappelle heredoc va cause de gnl
void	ft_heredoc(char *str, t_struct *repo, t_info *info)
{
	int		fd;
	char	*line;
	
	repo->i_heredoc = 1;
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		dup2(info->saved_stderr, STDERR_FILENO);
		printf("Minishell: %s: %s\n", "/tmp/heredoc.txt", strerror(errno));
		return ;
	}
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(str, line, ft_strlen(str)) == 0)
		{
			get_next_line(-1);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	fd = open("/tmp/heredoc.txt", O_RDONLY, 0644);
	if (fd == -1)
	{
		dup2(info->saved_stderr, STDERR_FILENO);
		printf("Minishell: %s: %s\n", "/tmp/heredoc.txt", strerror(errno));
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		dup2(info->saved_stderr, STDERR_FILENO);
		printf("Minishell: %s: %s\n", "/tmp/heredoc.txt", strerror(errno));
		close(fd);
		return ;
	}
	close(fd);
}