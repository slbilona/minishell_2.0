#include "../Minishell.h"

char	**ft_supprime_sous_chaine(char **str, int i)
{
	int		j;
	int		k;
	char	**s;

	j = 0;
	k = 0;
	s = malloc(sizeof(char *) * ft_count_double_string(str));
	if (!s)
		return (NULL);
	printf("test\n");
	while (str && str[k])
	{
		if (k == i)
		{
			k++;
		}
		else
		{
			s[j] = ft_strdup(str[k]);
			if (!s[j])
			{
				ft_free_split(s, j);
				return (NULL);
			}
			j++;
			k++;
		}
	}
	s[j] = NULL;
	ft_free_double_string(str);
	return (s);
}

// ne fonctionne pqs lorsqu'on qppelle la fonction env
void	ft_unset(t_struct *repo, void *inf)
{
	int		i;
	int		j;
	char	*var;
	t_info  *info;

	i = 0;
	j = 1;
	info = inf;
	while (repo->args[j])
	{
		var = ft_strjoin(repo->args[j], "=");
		printf("var : %s\n", var);
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
