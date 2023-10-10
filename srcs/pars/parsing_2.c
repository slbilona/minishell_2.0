/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:39:40 by ilona             #+#    #+#             */
/*   Updated: 2023/10/10 23:39:41 by ilona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

//initialise et renvoie le tableau de structure comptenant les commandes
t_struct	*ft_init_struct(t_info *info, char **str)
{
	t_struct	*repo;

	repo = ft_calloc(ft_count_double_string(str), sizeof(t_struct));
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
				ft_put_str_error("Minishell: erreur ", "de syntaxe près",
					" du symbole inattendu", " « newline »");
				ft_free_double_string(s);
				return (1);
			}
			else if ((s[j + 1] && ft_strchr(s[j + 1], '>'))
				|| (s[j + 1] && ft_strchr(s[j + 1], '<')))
			{
				ft_put_str_error("Minishell: syntax ",
					"error near unexpected token `", s[j + 1], "'");
				ft_free_double_string(s);
				return (1);
			}
		}
		j++;
	}
	return (0);
}

char	**ft_pars_s(t_info *info, char *str)
{
	char	**s;

	(void) info;
	s = ft_new_split(str, NULL);
	if (!s)
		return (ft_put_str_error("Minishell:", " erreur lors",
				" du split", " de la commande"), NULL);
	s = ft_clean_quotes(s);
	if (!s)
		return (ft_put_str_error("Minishell:", " erreur lors",
				" du split", " de la commande"), NULL);
	if (ft_verif_chevrons(s))
		return (NULL);
	return (s);
}

int	ft_cherche_redirection(t_struct *repo, char **s, int *j, int i)
{
	char	*str_joined;

	str_joined = ft_strjoin(s[*j], " ");
	repo[i].redirection = mange(repo[i].redirection,
			ft_strjoin(str_joined, s[*j + 1]), 1);
	free(str_joined);
	*j += 2;
	return (0);
}

int	ft_split_command(t_info *info, char **str, t_struct *repo)
{
	int		i;
	int		j;
	int		count;
	char	**s;

	i = 0;
	while (str && str[i])
	{
		repo[i].ret = 0;
		repo[i].nb_cmd = i;
		count = 0;
		s = ft_pars_s(info, str[i]);
		if (!s)
			return (1);
		j = 0;
		while (s && s[j])
		{
			if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0 || ft_strncmp(s[j],
					">>", sizeof(s[j])) == 0 || ft_strncmp(s[j], "<",
					sizeof(s[j])) == 0 || ft_strncmp(s[j], "<<",
					sizeof(s[j])) == 0)
			{
				ft_cherche_redirection(repo, s, &j, i);
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

/* Ajoute une sous chaine a une double chaine en la realouant
Si n == 0 s n'est pas free
Si n == 1 s est free */
char	**mange(char **str, char *s, int n)
{
	int		i;
	int		j;
	char	**s2;
	char	**ancien;

	i = 0;
	j = 0;
	if (!str)
	{
		s2 = malloc(sizeof(char *) * 2);
		if (!s2)
		{
			ft_put_str_error("Minishell:", "erreur lors de l'ajout de \"",
				s, "\" dans la double chaine");
			if (n)
				free(s);
			return (NULL);
		}
	}
	else
	{
		ancien = ft_cp_env(str);
		while (str && str[i])
			i++;
		s2 = malloc(sizeof(char *) * (i + 2));
		if (!s2)
		{
			ft_put_str_error("Minishell:", "erreur lors de l'ajout de '",
				s, "' dans la double chaine");
			if (n)
				free(s);
			return (ft_free_double_string(str), ancien);
		}
		while (str && str[j])
		{
			s2[j] = ft_strdup(str[j]);
			if (!s2[j])
			{
				ft_free_split(s2, j);
				ft_put_str_error("Minishell:", "erreur lors de l'ajout de '",
					s, "' dans la double chaine");
				if (n)
					free(s);
				return (ft_free_double_string(str), ancien);
			}
			j++;
		}
		ft_free_double_string(ancien);
	}
	s2[j] = ft_strdup(s);
	j++;
	s2[j] = NULL;
	if (n)
		free(s);
	ft_free_double_string(str);
	return (s2);
}
