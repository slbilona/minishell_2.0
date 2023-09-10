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

typedef struct s_info {
	int		nb_de_cmd;
}	t_info;

// Struct

t_struct	*ft_init_struct(char **str);
void	ft_split_command(char **str, t_struct *repo);

// Utils

char	**mange(char **str, char *s);
int		ft_count_cmd(char **str);

// pré parsing

char	*ft_pre_parsing(char *entree);

// Espaces

char	*ft_ajoute_espace(char *entree);

// Parsing 



// Exec

int ft_execution(t_struct *repo, t_info *info);

#endif