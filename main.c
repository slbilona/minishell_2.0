#include "Minishell.h"

int	main()
{
	char	*entree;
	char	**str;
	int i;
	while (1)
	{
		entree = readline("Minishell$ ");
		add_history(entree);
		str = ft_new_split(entree, "<>|");
		i = 0;
		while(str[i])
		{
			printf("str : %s\n", str[i]);
			i++;
		}
	// 	if (ft_pre_parsing(entree))
	// 		return (1);
	// 	str = ft_split(entree, '|');
	// 	ft_init_struct(str);
		free(entree);
	}
}
