#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
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
	int		i_heredoc;
	int		nb_cmd;
	char	*cmd;
	char	*path;
	char	**args;
	char	**redirection;
	int		num_after_chevron;
}	t_struct;

typedef struct s_builtins {
	char	*str;
	void	(*ptr)(t_struct *, void *);
}	t_builtins;

typedef struct s_info {
	int					nb_de_cmd;
	int					nb_de_pipe;
	int					saved_stdin;
	int					saved_stdout;
	int					saved_stderr;
	char				**env;
	pid_t				*diff_pid;
	struct s_builtins	builtins[7];
}	t_info;

// Struct

t_struct	*ft_init_struct(char **str);
int	ft_split_command(char **str, t_struct *repo);

// Utils

int			ft_trouve_egal(char *str);
int			ft_white_spaces(char *str);
int			ft_white_spaces(char *str);
int			ft_que_des_chiffres(char *str);
int			ft_print_tab(char **str, int j);
int			ft_count_double_string(char **str);
int			ft_long_atoi(char *str, long long int *num);
int			ft_cherche_dans_env(char *str, t_info *info, int o);
char		**ft_cp_env(char **ancien_env);
char		**ft_supprime_sous_chaine(char **str, int i);
char		**ft_new_split(const char *str, const char *sep);
void		ft_init_builtins(t_info *info);
void		ft_free_double_string(char **str);
void		ft_free_struct(t_struct *repo, t_info *info, int j);
void		ft_put_str_error(char *str1, char *str2, char *str3, char *str4);

// Parsing

int			main_parsing(char *str);
int			check_direction(char *str);
int			ft_compte_espaces(char *str);
int			check_left_direction(char *str);
int			check_right_direction(char *str);
char		*ft_pre_parsing(char *entree);
char		*ft_ajoute_espace(char *entree);
char		**mange(char **str, char *s, int n);
t_struct	*ft_init_struct(char **str);

// Exec

int			ft_execution_coordinateur(t_struct *repo, t_info *info);
int			ft_redirection(char **str, t_struct *repo, t_info *info);
char		*ft_cherche_path(t_struct *repo, t_info *info);
void		ft_heredoc(char *str, t_struct *repo, t_info *info);

// Builtins

int			ft_pwd(t_struct *repo, void *inf);
int			ft_env(t_struct *repo, void *inf);
int			ft_echo(t_struct *repo, void *inf);
int			ft_exit(t_struct *repo, void *inf);
int			ft_export(t_struct *repo, void *inf);
void		ft_cd(t_struct *repo, void *inf);
void		ft_unset(t_struct *repo, void *inf);

#endif