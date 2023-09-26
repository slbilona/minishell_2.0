#include "../Minishell.h"

// ne fonctionne pqs lorsqu'on qppelle la fonction env
void	ft_unset(t_struct *repo, void *inf)
{
	int		i;
	int		j;
	char	*var;
	t_info	*info;

	j = 1;
	info = inf;
	while (repo->args[j])
	{
		var = ft_strjoin(repo->args[j], "=");
		i = 0;
		while (info->env[i])
		{
			if (ft_strnstr(info->env[i], var, ft_strlen(var)))
			{
				info->env = ft_supprime_sous_chaine(info->env, i);
				//gerer le cas ou info->env est NULL
				break ;
			}
			else
				i++;
		}
		free(var);
		j++;
	}
}

int	ft_env(t_struct *repo, void *inf)
{
	int		i;
	t_info	*info;

	i = 0;
	info = inf;
	(void) repo;
	while (info->env[i])
	{
		if (write(1, info->env[i], ft_strlen(info->env[i])) == -1)
			return (perror("Minishell: env: erreur d'écriture "), 1);
		if (write(1, "\n", 1) == -1)
			return (perror("Minishell: env: erreur d'écriture "), 1);
		i++;
	}
	return (0);
}

// definir le comportement d'export sans argument (c'est indifini donc a nous de choisir)
int	ft_export(t_struct *repo, void *inf)
{
	int		j;
	int		o;
	int		ret;
	t_info	*info;

	j = 1;
	o = 0;
	ret = 0;
	info = inf;
	while (repo->args[j])
	{
		o = ft_trouve_egal(repo->args[j]);
		if (!ft_white_spaces(repo->args[j]) && o > 0)
		{
			if (!ft_cherche_dans_env(repo->args[j], info, o))
			{
				info->env = mange(info->env, repo->args[j], 0);
				//verifier si il n'y a pas une erreur;
			}
		}
		else if (o == -1)
		{
			ft_put_str_error("Minishell: export: `", repo->args[j], "': not a valid identifier", NULL);
			// dup2(info->saved_stderr, STDOUT_FILENO);
			// printf("Minishell: export: `%s': not a valid identifier\n", repo->args[j]);
			ret = 1;
		}
		j++;
	}
	return (ret);
}
