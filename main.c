#include "Minishell.h"

int	ft_pre_parsing(char *entree)
{
	int i;

	i = 0;
	while (entree[i])
	{
		if(entree[i] == '|')
		{
			if (entree[i + 1] && entree[i + 1] == '|')
				return (printf("minishell: erreur de syntaxe près du symbole inattendu « | »\n"), 1);
		}
		i++;
	}
}

int	main()
{
	char	*entree;
	char	**str;

	while (1)
	{
		entree = readline("Minishell$ ");
		if (ft_pre_parsing(entree))
		{

		}
		str = ft_split(entree, '|');
		ft_init_struct(str);
		printf("test\n");
	}
}
