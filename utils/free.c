#include "../Minishell.h"

void	ft_free_double_string(char **str)
{
	int	j;

	j = 0;
	if (str)
	{
		while (str[j])
		{
			free(str[j]);
			j++;
		}
		free(str);
	}
}