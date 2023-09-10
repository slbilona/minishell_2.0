#include "../Minishell.h"

t_struct *ft_init_struct(char **str)
{
	t_struct	*repo;

	repo = malloc (sizeof(t_struct) * ft_count_cmd(str)); //eventuellement uriliser calloc comme ca tout est deja initialiser a 0
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
				printf("%s %s : redirection\n", s[j], s[j + 1]);
				repo[i].redirection = mange(repo[i].redirection, ft_strjoin(s[j], ft_strjoin(" ", s[j + 1])));
				j += 2;
			}
			else if (count == 0)
			{
				printf("%s : cmd\n", s[j]);
				repo[i].cmd = s[j];
				count ++;
				j++;
			}
			else
			{
				printf("%s : args\n", s[j]);
				repo[i].args = mange(repo[i].args, s[j]);
				j++;
			}
		}
		free(s);
		i++;
	}
}

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
		{
			i++;
		}
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
	ft_free_double_string(str);
	return (s2);
}
