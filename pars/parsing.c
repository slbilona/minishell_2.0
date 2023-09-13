#include "../Minishell.h"

//initialise et renvoie le tableau de structure comptenant les commandes
t_struct *ft_init_struct(char **str)
{
	t_struct	*repo;

	repo = malloc (sizeof(t_struct) * ft_count_double_string(str)); //eventuellement uriliser calloc comme ca tout est deja initialiser a 0
	ft_split_command(str, repo);
	return repo;
}

void	ft_split_command(char **str, t_struct *repo)
{
	int		i;
	int		j;
	int		count;
	//int	k;
	char	**s;
	char	*str_joined;

	i = 0;
	//k = 0;
	while (str[i])
	{
		ft_memset(&repo[i], 0, sizeof(repo[i]));
		count = 0;
		s = ft_split(str[i], ' ');
		j = 0;
		while (s[j])
		{
			if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], ">>", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
			{
				//printf("%s %s : redirection\n", s[j], s[j + 1]);
				str_joined = ft_strjoin(" ", s[j + 1]);
				repo[i].redirection = mange(repo[i].redirection, ft_strjoin(s[j], str_joined)); //ajoute au char ** une string qu'on a join qui contient la string actuelle, un espace et la string suivante
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
				repo[i].cmd = s[j];
				count ++;
				j++;
			}
			else
			{
				//printf("%s : args\n", s[j]);
				repo[i].args = mange(repo[i].args, s[j]);
				j++;
			}
		}
		//ft_free_double_string(s);
		free(s);
		i++;
	}
}

char **mange(char **str, char *s)
{
	int i;
	int j;
	char **s2;

	i = 0;
	j = 0;
	if(!str)
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
	free(s);
	ft_free_double_string(str);
	return (s2);
}
