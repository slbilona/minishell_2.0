/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:17:01 by ilselbon          #+#    #+#             */
/*   Updated: 2023/10/06 00:35:13 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_put_str_error("exit", NULL, NULL, NULL);
	if (ft_count_double_string(repo->args) > 2)
	{
		return (ft_put_str_error("Minishell: ", "exit:", " too many arguments", NULL), 1);
	}
	else if (ft_count_double_string(repo->args) == 2)
	{
		if (ft_long_atoi(repo->args[1], &num) || ft_que_des_chiffres(repo->args[1]) || ft_signes(repo->args[1]))
		{
			ft_put_str_error("Minishell: exit: ", repo->args[1], ": numeric argument required", NULL);
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
int	ft_echo(t_struct *repo, void *inf)
{
	int	i;
	int	j;
	int	n;

	(void)inf;
	j = 1;
	i = 1;
	n = 1;
	while (repo->args && repo->args[i])
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
	if (ft_print_tab(repo->args, i))
		return (1);
	if (n == 1 || j == 1)
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (perror("Minishell: echo: erreur d'écriture "), 1);
	return (0);
}

// si getcwd echoue regarder dans l'env et si il n'y a pas dans l'env afficher une erreur
int	ft_pwd(t_struct *repo, void *inf)
{
	char	cwd[1000];

	(void) repo;
	(void) inf;
	;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("erreur\n"); // a changer
		return 1;
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

// n'affiche pas de msg d'erreur lorque on essaye d'entrer dans un fichier
int	ft_cd(t_struct *repo, void *inf)
{
	char	*home;
	t_info	*info;

	info = inf;
	if (ft_count_double_string(repo->args) > 2)
	{
		ft_put_str_error("Minishell: cd: trop d'arguments", NULL, NULL, NULL);
		return (1);
	}
	if (repo->args[1] && ft_strncmp(repo->args[1], "-", sizeof(repo->args[1])) == 0)
	{
		home = getenv("HOME");
		if (!home)
			return (perror("getenv"), 1);
		ft_export_pwd(info, 0);
		if (chdir(home))
		{
			ft_put_str_error("Minishell: cd: ", strerror(errno), NULL, NULL);
			return (1);
		}
		ft_pwd(repo, inf);
	}
	else if (!repo->args[1] || ft_strncmp(repo->args[1], "~", sizeof(repo->args[1])) == 0)
	{
		home = getenv("HOME");
		if (!home)
			return (perror("getenv"), 1);
		ft_export_pwd(info, 0);
		if (chdir(home))
		{
			ft_put_str_error("Minishell: cd: ", strerror(errno), NULL, NULL);
			return (1);
		}
	}
	else if (repo->args[1])
	{
		if (access(repo->args[1], F_OK) != 0)
		{
			ft_put_str_error("Minishell: cd: ", repo->args[1], ": Aucun fichier ou dossier de ce type", NULL);
			return (1);
		}
		if (!ft_directory_ou_non(repo->args[1]))
		{
			ft_put_str_error("Minishell: cd: ", repo->args[1], ": N'est pas", " un dossier");
			return (1);
		}
		ft_export_pwd(info, 0);
		if (chdir(repo->args[1]))
		{
			ft_put_str_error("Minishell: cd: ", strerror(errno), NULL, NULL);
			return (1);
		}
	}
	ft_export_pwd(info, 1);
	return (0);
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
