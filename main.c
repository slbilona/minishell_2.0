#include "Minishell.h"

int	main()
{
	char	*entree;
	
	while (1)
	{
		entree = readline("Minishell$ ");
		add_history(entree);
		ft_pre_parsing(entree);
	// 	if (ft_pre_parsing(entree))
	// 		return (1);
	// 	str = ft_split(entree, '|');
	// 	ft_init_struct(str);
		free(entree);
	}
}
