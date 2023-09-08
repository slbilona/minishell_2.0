#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
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

// Struct

void	ft_init_struct(char **str);
void	ft_split_command(char **str, t_struct *repo);

// Utils

int		ft_count_cmd(char **str);

// New split

char	**ft_new_split(char const *s, char* c);

int	ft_pre_parsing(char *entree);
void ft_ajoute_espace(char *entree);

#endif