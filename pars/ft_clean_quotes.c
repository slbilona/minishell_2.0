#include "../Minishell.h"

int	ft_q_taille(char *str)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (str && str[i])
	{
		if(ft_quotes(str, i) == 3 || ft_quotes(str, i) == 4)
			ret++;
		i++;
	}
	return (ft_strlen(str) - ret);
}

// Retire les guillemets ouvrant et fermant de str
char **ft_clean_quotes(char **str)
{
	int		i;
	int		j;
	int		k;
	int		taille;
	char	**s;

	i = 0;
	s = malloc(sizeof(char *) * (ft_count_double_string(str) + 1));
	// verifier
	while (str && str[i])
	{
		j = 0;
		k = 0;
		taille = ft_q_taille(str[i]);
		s[i] = malloc(sizeof(char) * (taille + 1));
		// verifier
		while (str[i][j])
		{
			if (ft_quotes(str[i], j) == 3 || ft_quotes(str[i], j) == 4)
				j++;
			else
			{
				s[i][k] = str[i][j];
				j++;
				k++;
			}
		}
		s[i][taille] = 0;
		i++;
	}
	s[i] = NULL;
	ft_free_double_string(str);
	return (s);
}
