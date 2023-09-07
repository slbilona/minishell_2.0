#include "Minishell.h"

void    ft_init_struct(char **str)
{   
	t_struct *repo;

	repo = malloc (sizeof(t_struct) * ft_count_cmd(str));
	ft_split_command(str, repo);
}


void ft_split_command(char **str, t_struct *repo)
{
	int i;
	int j;
	//int k;
	char **s;
	int count;

	j = 0;
	i = 0;
	//k = 0;
	count = 0;
	while(str[i])
	{
		s = ft_split(str[i], ' ');
		while (s[j])
		{
			if (ft_strncmp(s[j], ">", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], ">>", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<", sizeof(s[j])) == 0
				|| ft_strncmp(s[j], "<<", sizeof(s[j])) == 0)
			{
				printf("%s %s : redirection\n", s[j], s[j + 1]);
				//repo[i].redirection = ft_strjoin(s[0],s[1]);
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
				//repo[i].args = s[j];
				j++;
			}
		}
		free(s);
		i++;
	}
}
