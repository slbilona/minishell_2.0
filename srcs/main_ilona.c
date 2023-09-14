#include "../Minishell.h"

void ft_deux(t_struct *repo, void *inf)
{
    t_info *info = inf;
	printf("2 : repo->cmd : %s, info->nb_de_cmd : %d\n", repo->cmd, info->nb_de_cmd);
}

void ft_exit(t_struct *repo, void *inf)
{
    t_info *info = inf;
	printf("exit : repo->cmd : %s, info->nb_de_cmd : %d\n", repo->cmd, info->nb_de_cmd);
}

void ft_init_builtins(t_info *info)
{
	info->builtins[0].ptr = ft_exit;
	info->builtins[1].ptr = ft_deux;
	info->builtins[0].str = "exit";
	info->builtins[1].str = "deux";
}

int main()
{
    int i = 0;
    char str[] = "deux";
    t_info *info;
    t_struct *repo;

    repo = malloc(sizeof(t_struct));
    info = malloc(sizeof(t_info));
    ft_init_builtins(info);
    while(i < 2)
    {
        if(strncmp(str, info->builtins[i].str, strlen(info->builtins[i].str)) == 0)
        {
            info->builtins[i].ptr(repo, info);
            return 0;
        }
        else
            i++;
    }
    printf("nope\n");
    return 0;
}