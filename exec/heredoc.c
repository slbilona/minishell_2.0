/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:32:48 by ilona             #+#    #+#             */
/*   Updated: 2023/10/07 12:47:17 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_ouverture_heredoc(char *str, t_info *info)
{
	int		fd;
	char	*line;

	info->i_heredoc = 1;
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_put_str_error("Minishell: /tmp/heredoc.txt: ",
			strerror(errno), NULL, NULL);
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("erreur\n");
			break ;
		}
		if (ft_strncmp(str, line, ft_strlen(str) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (ft_verif_dollar(line))
			line = ft_expand_heredoc(info, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

int	ft_lecture_heredoc(void)
{
	int	fd;

	fd = open("/tmp/heredoc.txt", O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_put_str_error("Minishell: /tmp/heredoc.txt: ",
			strerror(errno), NULL, NULL);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_put_str_error("Minishell: /tmp/heredoc.txt: ",
			strerror(errno), NULL, NULL);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_heredoc_ou_non(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strncmp("<< ", str[i], 3) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_heredoc(t_info *info, char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strncmp("<< ", str[i], 3) == 0)
		{
			if (ft_ouverture_heredoc(str[i] + 3, info))
				return (1);
		}
		i++;
	}
	return (0);
}
