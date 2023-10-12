/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilona <ilona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:39:40 by ilona             #+#    #+#             */
/*   Updated: 2023/10/12 18:18:05 by ilona            ###   ########.fr       */
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

char	**ft_pars_s(t_info *info, char *str)
{
	char	**s;

	(void) info;
	s = ft_new_split(str, NULL);
	if (!s)
		return (ft_put_str_error("Minishell:", " erreur lors",
				" du split", " de la commande"), NULL);
	s = ft_expand_etc(info, s);
	if (!s)
		return (NULL);
	s = ft_clean_quotes(s);
	if (!s)
		return (ft_put_str_error("Minishell:", " erreur lors",
				" du split", " de la commande"), NULL);
	if (ft_verif_chevrons(s))
		return (NULL);
	return (s);
}

int	ft_cmd(t_struct *repo, char **s, int *j, int *count)
{
	repo->args = malloc(sizeof(char *) * 2);
	if (!repo->args)
	{
		ft_put_str_error("Minishell:", " erreur lors",
			" du split", " de la commande");
		ft_free_double_string(s);
		return (1);
	}
	repo->args[0] = ft_strdup(s[*j]);
	repo->args[1] = NULL;
	repo->cmd = ft_strdup(s[*j]);
	*count += 1;
	*j += 1;
	return (0);
}

int	ft_split_commande_suite(t_struct *repo, int i, char **s)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (s && s[j])
	{
		if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0 || ft_strncmp(s[j],
				">>", sizeof(s[j])) == 0 || ft_strncmp(s[j], "<",
				sizeof(s[j])) == 0 || ft_strncmp(s[j], "<<",
				sizeof(s[j])) == 0)
			ft_cherche_redirection(repo, s, &j, i);
		else if (count == 0)
		{
			if (ft_cmd(&repo[i], s, &j, &count))
				return (1);
		}
		else
		{
			repo[i].args = mange(repo[i].args, s[j], 0);
			j++;
		}
	}
	return (0);
}

int	ft_split_command(t_info *info, char **str, t_struct *repo)
{
	int		i;
	char	**s;

	i = 0;
	while (str && str[i])
	{
		repo[i].ret = 0;
		repo[i].nb_cmd = i;
		s = ft_pars_s(info, str[i]);
		if (!s)
			return (1);
		if (ft_split_commande_suite(repo, i, s))
			return (1);
		ft_free_double_string(s);
		i++;
	}
	return (0);
}
