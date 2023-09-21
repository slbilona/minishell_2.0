#include "../Minishell.h"

//initialise et renvoie le tableau de structure comptenant les commandes
t_struct	*ft_init_struct(char **str)
{
	t_struct	*repo;

	repo = ft_calloc(ft_count_double_string(str), sizeof(t_struct)); //j'ai remplacé par calloc comme ca ca initialise tous les elements a 0 et on a pas besoin d'utiliser memset plus tard
	//verifier si l'allocation a fonctionné
	ft_split_command(str, repo);
	return (repo);
}

int	ft_split_command(char **str, t_struct *repo)
{
	int		i;
	int		j;
	int		count;
	char	**s;
	char	*str_joined;

	i = 0;
	while (str[i])
	{
		count = 0;
		s = ft_new_split(str[i], NULL); // split aux white spaces
		j = 0;
		while(s[j])
		{
			if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], ">>", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
			{
				if(s[j + 1] == NULL)
				{
					printf("Rajoute un truc frero\n");
					return 1;
				}
			}
			j++;
		}
		j = 0;
		while (s[j])
		{
			if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], ">>", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
			{
				//printf("%s %s : redirection\n", s[j], s[j + 1]);
				str_joined = ft_strjoin(s[j], " ");
				repo[i].redirection = mange(repo[i].redirection, ft_strjoin(str_joined, s[j + 1]), 1); //ajoute au char ** une string qu'on a join qui contient la string actuelle, un espace et la string suivante
				free(str_joined);
				j += 2;
			}
			else if (count == 0)
			{
				//printf("%s : cmd\n", s[j]);
				//printf("repo[%d]\n", i);
				repo[i].args = malloc(sizeof(char *) * 2);
				repo[i].args[0] = ft_strdup(s[j]);
				repo[i].args[1] = NULL;
				repo[i].cmd = ft_strdup(s[j]);
				count ++;
				j++;
			}
			else
			{
				//printf("%s : args\n", s[j]);
				repo[i].args = mange(repo[i].args, s[j], 0);
				j++;
			}
		}
		ft_free_double_string(s);
		i++;
	}
	return (0);
}

/* ajoute une sous chaine a une double chaine en la realouant
si n est egal a 1 s est free sinon non*/
char	**mange(char **str, char *s, int n)
{
	int		i;
	int		j;
	char	**s2;

	i = 0;
	j = 0;
	if (!str)
	{
		s2 = malloc(sizeof(char *) * 2);
	}
	else
	{
		while (str[i])
			i++;
		s2 = malloc(sizeof(char *) * (i + 2));
		while (str[j])
		{
			s2[j] = ft_strdup(str[j]);
			j++;
		}
	}
	s2[j] = ft_strdup(s);
	j++;
	s2[j] = NULL;
	if (n)
		free(s);
	ft_free_double_string(str);
	return (s2);
}
