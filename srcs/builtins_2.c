#include "../Minishell.h"

//char **

// void	ft_unset(t_struct *repo, void *inf)
// {

// 	t_info  *info;

// 	info = inf;

// }

void	ft_env(t_struct *repo, void *inf)
{
	int     i;
	t_info  *info;

	i = 0;
	info = inf;
	(void) repo;
	while (info->env[i])
	{
		printf("%s\n", info->env[i]);
		i++;
	}
}
