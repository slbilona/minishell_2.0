#include "../Minishell.h"

void	ft_free_double_string(char **str)
{
	int	j;

	j = 0;
	if (str)
	{
		while (str[j])
		{
			if (str[j])
				free(str[j]);
			j++;
		}
		free(str);
	}
}

//free la structure repo ou info ou les deux
void	ft_free_struct(t_struct *repo, t_info *info, int j)
{
	int	i;

	if (repo && (j == 0 || j == 2))
	{
		i = 0;
		while (i < info->nb_de_cmd)
		{
			if (repo[i].cmd)
				free(repo[i].cmd);
			if (repo[i].path)
				free(repo[i].path);
			ft_free_double_string(repo[i].args);
			ft_free_double_string(repo[i].redirection);
			i++;
		}
		free(repo);
	}
	if (info && (j == 1 || j == 2))
	{
		ft_free_double_string(info->env);
		//if(info->saved_stdin)
			close(info->saved_stdin);
		close(info->saved_stdout);
		close(info->saved_stderr);
		free(info);
	}
}
