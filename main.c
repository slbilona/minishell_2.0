#include "Minishell.h"

int	main()
{
	char	*entree;
	char	**str;

	while (1)
	{
		entree = readline("Minishell$ ");
		str = ft_split(entree, '|');
		ft_init_struct(str);
	}
}
