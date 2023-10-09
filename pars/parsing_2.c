#include "../Minishell.h"

//initialise et renvoie le tableau de structure comptenant les commandes
t_struct	*ft_init_struct(t_info *info, char **str)
{
	t_struct	*repo;

	repo = ft_calloc(ft_count_double_string(str), sizeof(t_struct)); //j'ai remplacé par calloc comme ca ca initialise tous les elements a 0 et on a pas besoin d'utiliser memset plus tard
	if (!repo)
		return (NULL);
	if (ft_split_command(info, str, repo))
	{
		info->nb_de_cmd = ft_count_double_string(str);

		return (ft_free_struct(repo, info, 0), NULL);
	}
	return (repo);
}

int	ft_verif_chevrons(char **s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0
			|| ft_strncmp(s[j], ">>", sizeof(s[j])) == 0
			|| ft_strncmp(s[j], "<", sizeof(s[j])) == 0
			|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
		{
			if (s[j + 1] == NULL)
			{
				ft_put_str_error("Minishell: erreur ", "de syntaxe près", " du symbole inattendu", " « newline »");
				ft_free_double_string(s);
				return (1);
			}
			else if ((s[j + 1] && ft_strchr(s[j + 1], '>')) || (s[j + 1] && ft_strchr(s[j + 1], '<')))
			{
				ft_put_str_error("Minishell: syntax ", "error near unexpected token `", s[j + 1], "'");
				ft_free_double_string(s);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	ft_split_command(t_info *info, char **str, t_struct *repo)
{
	int		i;
	int		j;
	int		count;
	char	**s;
	char	*str_joined;

	i = 0;
	while (str && str[i])
	{
		repo[i].ret = 0;
		repo[i].nb_cmd = i;
		count = 0;
		s = ft_new_split(str[i], NULL);
		if (!s)
			return (ft_put_str_error("Minishell:", " erreur lors",
				" du split", " de la commande"), 1);
		if (ft_expand(info, s))
		{
			ft_free_double_string(s);
			return (1);
		}
		s = ft_clean_quotes(s);
		if (!s)
			return (ft_put_str_error("Minishell:", " erreur lors",
				" du split", " de la commande"), 1);
		if (ft_verif_chevrons(s))
			return (1);
		j = 0;
		while (s && s[j])
		{
			if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], ">>", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
			{
				str_joined = ft_strjoin(s[j], " ");
				repo[i].redirection = mange(repo[i].redirection, ft_strjoin(str_joined, s[j + 1]), 1); //ajoute au char ** une string qu'on a join qui contient la string actuelle, un espace et la string suivante
				free(str_joined);
				j += 2;
			}
			else if (count == 0)
			{
				repo[i].args = malloc(sizeof(char *) * 2);
				repo[i].args[0] = ft_strdup(s[j]);
				repo[i].args[1] = NULL;
				repo[i].cmd = ft_strdup(s[j]);
				count ++;
				j++;
			}
			else
			{
				repo[i].args = mange(repo[i].args, s[j], 0);
				j++;
			}
		}
		ft_free_double_string(s);
		i++;
	}
	return (0);
}

/* ajoute une sous chaine a une double chaine en la realouant
si n est egal a 1 s est free sinon non*/
char	**mange(char **str, char *s, int n)
{
	int		i;
	int		j;
	char	**s2;

	i = 0;
	j = 0;
	if (!str)
	{
		s2 = malloc(sizeof(char *) * 2);
		if (!s2)
		{
			if (n)
				free(s);
			return (ft_free_double_string(str), NULL);
		}
	}
	else
	{
		while (str && str[i])
			i++;
		s2 = malloc(sizeof(char *) * (i + 2));
		if (!s2)
		{
			if (n)
				free(s);
			return (ft_free_double_string(str), NULL);
		}
		while (str && str[j])
		{
			s2[j] = ft_strdup(str[j]);
			// eventuellement verifier l'allocaztion jsp
			j++;
		}
	}
	s2[j] = ft_strdup(s);
	j++;
	s2[j] = NULL;
	if (n)
		free(s);
	ft_free_double_string(str);
	return (s2);
}
