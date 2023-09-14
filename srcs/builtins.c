#include "../Minishell.h"

int ft_exit(t_struct *repo, void *inf)
{
	int				exit_num;
	long long int	num;

	num = 0;
	exit_num = 0;
	// if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
	// {
	// 	perror("Erreur lors de la redirection de la sortie standard");
	// 	return (1);
	// }
	printf("exit\n");
	if (ft_count_double_string(repo->args) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (ft_count_double_string(repo->args) == 2)
	{
		if (ft_long_atoi(repo->args[1], &num) || ft_que_des_chiffres(repo->args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", repo->args[1]);
			exit_num = 2;
		}
		if (exit_num)
		{
			ft_free_struct(repo, (t_info *)inf, 2);
			exit(exit_num);
		}
	}
	ft_free_struct(repo, (t_info *)inf, 2);
	exit(num);
}

void	ft_echo(t_struct *repo, void *inf)
{
	int i;
	int j;
	int n;

	(void)inf;
	j = 1;
	i = 1;
	n = 1;
	if (repo->args && repo->args[i][0] == '-')
	{
		while (repo->args[i][j] == 'n')
			j++;
		if (repo->args[i][j] == 0)
		{
			j = 0;
			i++;
			n = 0;
		}
		else
			j = 0;
	}
	ft_print_tab(repo->args, i);
	if (n == 1 || j == 1)
		printf("\n");
}

void	ft_init_builtins(t_info *info)
{
	info->builtins[0].ptr = (void *)ft_exit;
	info->builtins[1].ptr = (void *)ft_echo;
	info->builtins[2].ptr = NULL;
	info->builtins[0].str = "exit";
	info->builtins[1].str = "echo";
	info->builtins[2].str = "deux";
}
