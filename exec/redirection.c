#include "../Minishell.h"

int	ft_redirection(char **str)
{
	int	i;
	int	fd;

	i = 0;
	while (str && str[i])
	{
		if (ft_strncmp("> ", str[i], 2) == 0)
		{
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
		}
		else if (ft_strncmp(">> ", str[i], 3) == 0)
		{
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
		}
		else if (ft_strncmp("< ", str[i], 2) == 0)
		{
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
		}
		else if (ft_strncmp("<< ", str[i], 3) == 0)
		{
			if (ft_lecture_heredoc())
				return (1);
		}
		i++;
	}
	return (0);
}
