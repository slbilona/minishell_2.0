#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft_printf_gnl/libft.h"
# include "libft_printf_gnl/get_next_line.h"
# include "libft_printf_gnl/ft_printf.h"
# include <sys/stat.h>

typedef struct s_struct {
	char	*cmd;
	char	**args;
	char	**redirection;
}	t_struct;

//struct

void	ft_init_struct(char **str);
void	ft_split_command(char **str, t_struct *repo);

//utils

int		ft_count_cmd(char **str);

#endif