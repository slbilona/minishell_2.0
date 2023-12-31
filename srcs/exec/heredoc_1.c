/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:32:48 by ilona             #+#    #+#             */
/*   Updated: 2023/10/14 18:06:53 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_ouverture_heredoc_suite(t_info *info, char **line, char *str, int fd)
{
	(void)fd;
	if (!*line)
	{
		ft_put_str_error("Minishell: avertissement : « here-document » ",
			"délimité par la fin du fichier (au lieu de « ", str, " »)");
		return (1);
	}
	if (ft_strncmp(str, *line, ft_strlen(str) + 1) == 0)
	{
		free(*line);
		return (1);
	}
	if (ft_verif_dollar(*line))
	{
		*line = ft_expand_heredoc(info, *line);
		if (!*line)
		{
			ft_put_str_error("Minishell:", " erreur ",
				"lors du ", "heredoc");
			return (1);
		}
	}
	return (0);
}

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
	signal(SIGINT, ft_ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (ft_signaux_heredoc(info, fd))
			return (1);
		if (ft_ouverture_heredoc_suite(info, &line, str, fd))
			break ;
		if (ft_write_heredoc(line, fd))
			return (1);
		free(line);
	}
	return (close(fd), 0);
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

int	ft_heredoc_deux(t_info *info, char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strncmp("<< ", str[i], 3) == 0)
		{
			if (ft_ouverture_heredoc(str[i] + 3, info))
			{
				info->exit = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
