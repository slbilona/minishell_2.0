/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mange.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:12:18 by ilona             #+#    #+#             */
/*   Updated: 2023/10/14 16:22:11 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_mange_suite(char **str, char *s, char **s2, int n)
{
	int	j;

	j = -1;
	if (!s2)
	{
		ft_put_str_error("Minishell:", "erreur lors de l'ajout de '",
			s, "' dans la double chaine");
		if (n)
			free(s);
		return (ft_free_double_string(str), -1);
	}
	while (str && str[++j])
	{
		s2[j] = ft_strdup(str[j]);
		if (!s2[j])
		{
			ft_free_split(s2, j);
			ft_put_str_error("Minishell:", "erreur lors de l'ajout de '",
				s, "' dans la double chaine");
			if (n)
				free(s);
			return (ft_free_double_string(str), -1);
		}
	}
	return (j);
}

int	ft_verif_s2(char **s2, int n, char *s)
{
	if (!s2)
	{
		ft_put_str_error("Minishell:", "erreur lors de l'ajout de \"",
			s, "\" dans la double chaine");
		if (n)
			free(s);
		return (1);
	}
	return (0);
}

void	ft_post_mange(char **s2, char *s, int n, int j)
{
	s2[j] = ft_strdup(s);
	j++;
	s2[j] = NULL;
	if (n)
		free(s);
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

	j = 0;
	if (!str)
	{
		s2 = malloc(sizeof(char *) * 2);
		if (ft_verif_s2(s2, n, s))
			return (NULL);
	}
	else
	{
		ancien = ft_cp_env(str);
		s2 = malloc(sizeof(char *) * (ft_count_double_string(str) + 2));
		i = ft_mange_suite(str, s, s2, n);
		if (i == -1)
			return (ancien);
		else
			j += i;
		ft_free_double_string(ancien);
	}
	ft_post_mange(s2, s, n, j);
	return (ft_free_double_string(str), s2);
}
