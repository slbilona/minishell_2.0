/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:33:22 by ilona             #+#    #+#             */
/*   Updated: 2023/10/10 20:01:16 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

/* Si n == 1 free line
Si n == 0 ne free pas line */
char	*ft_cree_dest_heredoc(t_info *info, char *line, int k, int n)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& line[i + 1] == '?')
			i += ft_cree_dest_exit(info, dest, &j);
		else if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
			i += ft_cree_dest_suite(info, dest, &j, &line[i]);
		else if (line[i])
			dest[j++] = line[i++];
	}
	dest[j] = 0;
	if (n)
		free(line);
	return (dest);
}

char	*ft_expand_heredoc(t_info *info, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] == '?')
		{
			ft_j_et_k_exit(info, &j, &k);
		}
		else if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
			ft_change_j_et_k(info, &line[i], &j, &k);
		i++;
	}
	dest = ft_cree_dest_heredoc(info, line, ft_strlen(line) - j + k, 0);
	if (!dest)
		return (NULL);
	free(line);
	return (dest);
}
