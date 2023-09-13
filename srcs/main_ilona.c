#include "../Minishell.h"

void ft_deux()
{
	printf("fonction 2\n");
}

void ft_exit()
{
	printf("exit\n");
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
    char str[] = "exit";
    t_info *info;

    info = malloc(sizeof(t_info));
    ft_init_builtins(info);
    while(i < 2)
    {
        if(strncmp(str, info->builtins[i].str, strlen(info->builtins[i].str)) == 0)
        {
            info->builtins[i].ptr();
            return 0;
        }
        else
            i++;
    }
    printf("nope\n");
    return 0;
}