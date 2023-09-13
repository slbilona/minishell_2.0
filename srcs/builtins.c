#include "../Minishell.h"

int ft_exit(t_struct *repo, t_info *info)
{
	long long int	num;
	int				exit_num;

	num = 0;
	exit_num = 0;
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
			printf("minishell: exit: %s: numeric argument required\n", str[1]);
			exit_num = 2;
		}
		if (exit_num)
			exit(exit_num);
	}
	exit(num);
}
