#include "Minishell.h"

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(1,&str[i],1);
		i++;
	}
	printf("\n");
}

int	main()
{
	char	*entree;
	char	**str;
	int i;

	i = 0;
	
	while (1)
	{
		
		entree = readline("Minishell$ ");
		str = ft_split(entree, '|');
		
		ft_init_struct(str);
	}
}
