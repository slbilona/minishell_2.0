/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:17:01 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/07 14:27:11 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// si getcwd echoue regarder dans l'env et si il n'y a pas dans l'env afficher une erreur
int	ft_pwd(t_struct *repo, void *inf)
{
	char	cwd[1000];

	(void) repo;
	(void) inf;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("erreur\n"); // a changer
		return (1);
	}
	if (write(1, cwd, ft_strlen(cwd)) == -1)
		return (perror("Minishell: pwd: erreur d'écriture "), 1);
	if (write(1, "\n", 1) == -1)
		return (perror("Minishell: pwd: erreur d'écriture "), 1);
	return (0);
}

/* Si i == 0 : change la variable de OLDPWD
Si i == 1 : change la valeur de la variable PWD */
void	ft_export_pwd(t_info *info, int i)
{
	int		o;
	char	*var;
	char	cwd[1000];

	o = 0;
	if (i == 0 || i == 1)
		getcwd(cwd, sizeof(cwd)); // verifier si cwd n'echoue pas
	if (i == 1)
		var = ft_strjoin("PWD=", cwd);
	else if (i == 0)
		var = ft_strjoin("OLDPWD=", cwd);
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
