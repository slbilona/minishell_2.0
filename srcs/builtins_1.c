#include "../Minishell.h"

int	ft_exit(t_struct *repo, void *inf)
{
	int				exit_num;
	t_info			*info;
	long long int	num;

	num = 0;
	info = inf;
	exit_num = 0;
	if (dup2(info->saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	printf("exit\n");
	if (ft_count_double_string(repo->args) > 2)
	{
		printf("Minishell: exit: too many arguments\n");
		return (1);
	}
	else if (ft_count_double_string(repo->args) == 2)
	{
		if (ft_long_atoi(repo->args[1], &num) || ft_que_des_chiffres(repo->args[1]))
		{
			printf("Minishell: exit: %s: numeric argument required\n", repo->args[1]);
			exit_num = 2;
		}
		if (exit_num)
		{
			get_next_line(-1);
			ft_free_struct(repo, info, 2);
			exit(exit_num);
		}
	}
	get_next_line(-1);
	ft_free_struct(repo, info, 2);
	exit(num);
}

//pb lorsqu'on redirige et qu'on utilise l'argument -n
void	ft_echo(t_struct *repo, void *inf)
{
	int	i;
	int	j;
	int	n;

	(void)inf;
	j = 1;
	i = 1;
	n = 1;
	while (repo->args[i])
	{
		if (repo->args[i][0] == '-')
		{
			j = 1;
			while (repo->args[i][j] == 'n')
				j++;
			if (repo->args[i][j] == 0)
			{
				j = 0;
				i++;
				n = 0;
			}
			else
			{
				j = 0;
				break ;
			}
		}
		else
			break ;
	}
	ft_print_tab(repo->args, i);
	if (n == 1 || j == 1)
		write(STDOUT_FILENO, "\n", 1);
}

void	ft_pwd(t_struct *repo, void *inf)
{
	char	cwd[1000];

	(void) repo;
	(void) inf;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}

void	ft_export_pwd(t_info * info)
{
	int		o;
	char	*pwd;
	char	cwd[1000];
	
	o = 0;
	getcwd(cwd, sizeof(cwd));
	pwd = ft_strjoin("PWD=", cwd);
	if (pwd)
	{
		o = ft_trouve_egal(pwd);
		if (!ft_white_spaces(pwd) && o > 0)
		{
			if (!ft_cherche_dans_env(pwd, info, o))
			{
				info->env = mange(info->env, pwd, 0);
				//verifier si il n'y a pas une erreur;
			}
		}
	}
}

void	ft_cd(t_struct *repo, void *inf)
{
	char	*home;
	t_info	*info;

	info = inf;
	if (ft_count_double_string(repo->args) > 2)
	{
		dup2(info->saved_stderr, STDERR_FILENO);
		printf("Minishell: cd: trop d'arguments\n");
		return ;
	}
	if (repo->args[1] && ft_strncmp(repo->args[1], "-", sizeof(repo->args[1])) == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("getenv");
			return ;
		}
		chdir(home);
		ft_pwd(repo, inf);
	}
	else if (!repo->args[1] || ft_strncmp(repo->args[1], "~", sizeof(repo->args[1])) == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			perror("getenv");
			return ;
		}
		chdir(home);
	}
	else if (repo->args[1])
	{
		if (access(repo->args[1], F_OK) != 0)
		{
			dup2(info->saved_stdout, STDOUT_FILENO);
			printf("Minishell: cd: %s: Aucun fichier ou dossier de ce type\n", repo->args[1]);
			return ;
		}
		chdir(repo->args[1]);
	}
	ft_export_pwd(info);
}

void	ft_init_builtins(t_info *info)
{
	info->builtins[0].ptr = (void *)ft_exit;
	info->builtins[1].ptr = (void *)ft_echo;
	info->builtins[2].ptr = (void *)ft_cd;
	info->builtins[3].ptr = (void *)ft_pwd;
	info->builtins[4].ptr = (void *)ft_env;
	info->builtins[5].ptr = (void *)ft_unset;
	info->builtins[6].ptr = (void *)ft_export;
	info->builtins[0].str = "exit";
	info->builtins[1].str = "echo";
	info->builtins[2].str = "cd";
	info->builtins[3].str = "pwd";
	info->builtins[4].str = "env";
	info->builtins[5].str = "unset";
	info->builtins[6].str = "export";
}
