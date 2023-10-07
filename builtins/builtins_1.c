/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:17:01 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/07 21:57:56 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	ft_pwd_suite(char *pwd)
{
	if (write(1, pwd, ft_strlen(pwd)) == -1)
		return (perror("Minishell: pwd: erreur d'écriture "), 1);
	free(pwd);
	if (write(1, "\n", 1) == -1)
		return (perror("Minishell: pwd: erreur d'écriture "), 1);
	return (0);
}

int	ft_pwd(t_struct *repo, void *inf)
{
	char	*pwd;
	char	cwd[1000];

	(void) repo;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		pwd = my_getenv((t_info *) inf, "PWD");
		if (!pwd)
		{
			return (ft_put_str_error("Minishell:", " pwd: ",
					"repertoire ", "inexistant"), 1);
		}
		else
			return (ft_pwd_suite(pwd));
	}
	if (write(1, cwd, ft_strlen(cwd)) == -1)
		return (perror("Minishell: pwd: erreur d'écriture "), 1);
	if (write(1, "\n", 1) == -1)
		return (perror("Minishell: pwd: erreur d'écriture "), 1);
	return (0);
}

char	*ft_export_pwd_suite(t_info *info, int i, char *pwd)
{
	char	*var;
	char	cwd[1000];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		if (i == 1)
			pwd = my_getenv(info, "PWD");
		else
			pwd = my_getenv(info, "OLDPWD");
		if (i == 1)
			var = ft_strjoin("PWD=", pwd);
		else if (i == 0)
			var = ft_strjoin("OLDPWD=", pwd);
		if (pwd)
			free(pwd);
	}
	else
	{
		if (i == 1)
			var = ft_strjoin("PWD=", cwd);
		else if (i == 0)
			var = ft_strjoin("OLDPWD=", cwd);
	}
	return (var);
}

/* Si i == 0 : change la variable de OLDPWD
Si i == 1 : change la valeur de la variable PWD */
void	ft_export_pwd(t_info *info, int i)
{
	int		o;
	char	*var;
	char	*pwd;

	o = 0;
	pwd = NULL;
	if (i == 0 || i == 1)
		var = ft_export_pwd_suite(info, i, pwd);
	if (var)
	{
		o = ft_trouve_egal(var);
		if (!ft_white_spaces(var) && o > 0)
		{
			if (!ft_cherche_dans_env(var, info, o))
			{
				info->env = mange(info->env, var, 1);
				//verifier si il n'y a pas une erreur;
			}
			else
				free(var);
		}
	}
}
