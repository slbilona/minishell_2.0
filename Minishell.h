#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft_printf_gnl/libft.h"
# include "libft_printf_gnl/ft_printf.h"
# include "libft_printf_gnl/get_next_line.h"

typedef struct s_struct {
	char	*cmd;
	char	**args;
	char	**redirection;
}	t_struct;

typedef struct s_info {
	int		nb_de_cmd;
	char	*path;
	char	**env;
}	t_info;

// Utils

int			ft_count_cmd(char **str);
void		ft_free_double_string(char **str);
void		ft_free_struct(t_struct *repo, t_info *info, int j);

// pré parsing

char		*ft_pre_parsing(char *entree);

// Espaces

int			ft_compte_espaces(char *str);
char		*ft_ajoute_espace(char *entree);

// Parsing 

char		**mange(char **str, char *s);
void		ft_split_command(char **str, t_struct *repo);
t_struct	*ft_init_struct(char **str);

// Exec

int			ft_execution(t_struct *repo, t_info *info);

#endif