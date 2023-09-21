/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:32:48 by ilona             #+#    #+#             */
/*   Updated: 2023/09/21 13:31:27 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_verif_dollar(char *line)
{
	char *str;
	
	str = ft_strrchr(line, '$');
	if (str && str[1] && (str[1] < 9 || 13 < str[1]) && str[1] != 32)
		return (1);
	return (0);
}

char	*ft_expand_heredoc(t_info *info, char *line)
{
	
}

// ajouter un moyen pour se balader dans la ligne qu'on est en trqin d'ecrire dans le trminal en utilisant les fleches
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
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(str, line, ft_strlen(str) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (ft_verif_dollar(line))
		{
			printf("dollar trouve\n");
			line = ft_expand_heredoc(info, line);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
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