#include "../Minishell.h"

int	ft_new_compte_mot(const char *str, const char *sep)
{
	int	i;
	int	compte;

	i = 0;
	compte = 0;
	while (str && str[i])
	{
		while (str[i] && ft_strchr(sep, str[i]))
			i++;
		if (str[i])
			compte++;
		while (str[i] && !ft_strchr(sep, str[i]))
			i++;
		i++;
	}
	return (compte);
}

char **new_split(const char *str, const char *sep)
{
	char **dest;

	dest = malloc(sizeof(char *) * (ft_new_compte_mot(str, sep)))
}