#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stddef.h>
# include <signal.h>
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
	int		ret;
	char	*cmd;
	char	*path;
	int		nb_cmd;
	char	**args;
	char	**redirection;
	int		num_after_chevron;
}	t_struct;

typedef struct s_builtins {
	char	*str;
	int		(*ptr)(t_struct *, void *);
}	t_builtins;

typedef struct s_info {
	int					i;
	int					fork;
	int					exit;
	int					i_heredoc;
	int					nb_de_cmd;
	int					i_diff_pid;
	int					nb_de_pipe;
	int					saved_stdin;
	int					saved_stdout;
	int					saved_stderr;
	char				**env;
	pid_t				*diff_pid;
	struct s_builtins	builtins[7];
}	t_info;

// Struct

int			ft_split_command(t_info *info, char **str, t_struct *repo);
t_struct	*ft_init_struct(t_info *info, char **str);

// Utils

int			ft_signes(char *str);
int			ft_trouve_egal(char *str);
int			ft_white_spaces(char *str);
int			ft_verif_dollar(char *line);
int			ft_ex_verif_dollar(char *line);
int			ft_que_des_chiffres(char *str);
int			ft_print_tab(char **str, int j);
int			ft_directory_ou_non(char *path);
int			ft_count_double_string(char **str);
int			ft_long_atoi(char *str, long long int *num);
int			ft_cherche_dans_env(char *str, t_info *info, int o);
int			ft_change_j_et_k(t_info *info, char *str, int *j, int *k);
char		**ft_cp_env(char **ancien_env);
char		*my_getenv(t_info *info, char *str);
char		*ft_cree_var(int j, char *str, int o);
int			**ft_free_prec_pipe(int **pipe_fd, int i);
char		**ft_supprime_sous_chaine(char **str, int i);
char		**ft_new_split(const char *str, const char *sep);
void		ft_j_et_k_exit(t_info *info, int *j, int *k);
void		ft_put_str_error(char *str1, char *str2, char *str3, char *str4);

// Signaux

void		handle_sigint(int sig);
void		ft_ctrl_d(t_info *info, char *entree);

// Parsing

int			main_parsing(char *str);
int			ft_check_pipe(char *str);
int			ft_compte_espaces(char *str);
int			ft_check_pipe_suite(char *str);
int			ft_check_pipe_prems(char *str);
int			check_left_direction(char *str);
int			check_right_direction(char *str);
int			ft_quotes(const char *str, int i);
int			parsing_exec(t_info *info, char *entree);
int			ft_check_pipe_suite_2(int i, char *str, int *o, int count_pipe);
char		**ft_clean_quotes(char **str);
char		*ft_ajoute_espace(char *entree);
char		**mange(char **str, char *s, int n);
t_struct	*ft_init_struct(t_info *info, char **str);

// Expand

int			ft_expand(t_info *info, char **str);
char		**ft_expand_test(t_info *info, char **str);
int			ft_cree_dest_exit(t_info *info, char *dest, int *j);
int			ft_cree_dest_suite(t_info *info, char *dest, int *j, char *c);
char		*ft_expand_heredoc(t_info *info, char *line);
char		*ft_cree_dest(t_info *info, char *line, int k, int n);

// Exec

int			ft_execution_coordinateur(t_struct *repo, t_info *info);
char		*ft_cherche_path(t_struct *repo, t_info *info);

// Builtins

int			ft_pwd(t_struct *repo, void *inf);
int			ft_env(t_struct *repo, void *inf);
int			ft_echo(t_struct *repo, void *inf);
int			ft_exit(t_struct *repo, void *inf);
int			ft_export(t_struct *repo, void *inf);
int			ft_cd(t_struct *repo, void *inf);
int			ft_unset(t_struct *repo, void *inf);
int			ft_builtins(t_struct *repo, t_info *info);
int			ft_exit_pipe(t_struct *repo, void *inf, int **pipes_fd);
int			ft_builtins_pipe(t_struct *repo, t_info *info, int **pipes_fd);
void		ft_export_pwd(t_info *info, int i);
void		ft_exit_suite(t_struct *repo, t_info *info,
				long long int *num, int *exit_num);

// Init

int			**ft_init_pipe(t_info *info);
int			ft_init_info_deux(t_info *info, int i);
void		ft_init_builtins(t_info *info);
void		ft_init_sep(char *sep);
t_info		*ft_init_info(char **env);

// Heredoc

int			ft_lecture_heredoc(void);
int			ft_heredoc_ou_non(char **str);
int			ft_write_heredoc(char *line, int fd);
int			ft_heredoc_deux(t_info *info, char **str);
int			ft_ouverture_heredoc(char *str, t_info *info);
int			ft_ouverture_heredoc_suite(t_info *info, char **line, char *str);

// Redirection

int			ft_redirection(char **str);
int			ft_redirection_input(char **str, int i);
int			ft_redirection_output(char **str, int i);
int			ft_redirection_output_append(char **str, int i);


// Free

int			**ft_free_pipe(t_info *info, int **pipes_fd);
void		ft_free_double_string(char **str);
void		ft_free_struct(t_struct *repo, t_info *info, int j);

#endif