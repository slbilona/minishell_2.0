#include "../Minishell.h"

/* Si n == 1 free line
Si n == 0 ne free pas line */
char	*ft_cree_dest_heredoc(t_info *info, char *line, int k, int n)
{
	int		i; // parcours line
	int		j; // parcours dest
	int		o;
	int		l; // parcours l'env
	char	*dest;
	char	*test;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&&  line[i + 1] == '?')
		{
			test = ft_itoa(info->exit);
			o = 0;
			while (test && test[o])
				dest[j++] = test[o++];
			i += 2;
			free(test);
		}
		else if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
		{
			o = 0;
			l = ft_change_j_et_k(info, &line[i], &o, &k);
			i += o;
			if (l > -1)
			{
				while (info->env && info->env[l] && info->env[l][o])
					dest[j++] = info->env[l][o++];
			}
		}
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
	//(void) info;
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
	// Verifier la string
	free(line);
	return (dest);
}