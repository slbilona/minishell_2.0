/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 01:00:53 by ilona             #+#    #+#             */
/*   Updated: 2023/09/10 16:48:50 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void    ft_redirection(char **str)
{
	int i;
	int fd;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp("> ", str[i], 2))
		{
			fd = open(str[i] + 2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("Erreur lors de la redirection de la sortie standard");
        		return ;
			}
		}
		else
			printf("ilona\n");
		i++;
	}
	printf("hey\ntoi\n");
	close(fd);
	dup2(STDOUT_FILENO, STDOUT_FILENO);
}

int ft_execution(t_struct *repo, t_info *info)
{
	int i;

	i = 0;
	while(i < info->nb_de_cmd)
	{
		if (repo[i].redirection)
			ft_redirection(repo[i].redirection);
		else
			printf("test\n");
		i++;
	}
	
	return (0);
}