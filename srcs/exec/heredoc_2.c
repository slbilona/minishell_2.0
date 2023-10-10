/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:00:11 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/10 16:00:25 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_write_heredoc(char *line, int fd)
{
	if (write(fd, line, ft_strlen(line)) == -1)
	{
		close(fd);
		free(line);
		return (perror("Minishell: echo: erreur d'écriture "), 1);
	}
	if (write(fd, "\n", 1) == -1)
	{
		close(fd);
		free(line);
		return (perror("Minishell: echo: erreur d'écriture "), 1);
	}
	return (0);
}
