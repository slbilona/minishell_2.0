/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:32:48 by ilona             #+#    #+#             */
/*   Updated: 2023/09/27 17:14:40 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

// verifie si il y a un dollar suivi d'un caractere visible
int	ft_verif_dollar(char *line)
{
	char	*str;

	str = ft_strrchr(line, '$');
	if (str && str[1] && (str[1] < 9 || 13 < str[1]) && str[1] != 32)
	{
		return (1);
	}
	return (0);
}

// genre de strjoin pour creer ma variable suivie d'un '='
char	*ft_cree_var(int j, char *str)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * (j + 1));
	while (i < j - 1)
	{
		var[i] = str[i + 1];
		i++;
	}
	var[i] = '=';
	var[i + 1] = 0;
	return (var);
}

/* j */
int	ft_change_j_et_k(t_info *info, char *str, int *j, int *k)
{
	int		i;
	char	*var;

	i = 1;
	*j += 1;
	while (str && str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		*j += 1;
	}
	var = ft_cree_var(i, str);
	i = 0;
	while (info->env[i])
	{
		if (ft_strncmp(var, info->env[i], ft_strlen(var)) == 0)
		{
			*k += ft_strlen(info->env[i]) - ft_strlen(var);
			free(var);
			return (i);
		}
		i++;
	}
	free(var);
	return (-1);
}

/* Si n == 1 free line
Si n == 0 ne free pas line
*/
char	*ft_cree_dest(t_info *info, char *line, int k, int n)
{
	int		i; // parcours line
	int		j; // parcours dest
	int		o;
	int		l; // parcours l'env
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
		{
			o = 0;
			l = ft_change_j_et_k(info, &line[i], &o, &k);
			i += o;
			if (l > -1)
			{
				while (info->env[l][o])
					dest[j++] = info->env[l][o++];
			}
		}
		else if (line[i])
			dest[j++] = line[i++];
	}
	dest[j] = 0;
	if (n)
		free(line);
	return (dest);
}

char	*ft_expand_heredoc(t_info *info, char *line)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	i = 0;
	j = 0;
	k = 0;
	(void) info;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
			ft_change_j_et_k(info, &line[i], &j, &k);
		i++;
	}
	dest = ft_cree_dest(info, line, ft_strlen(line) - j + k, 0);
	// Verifier la string
	free(line);
	return (dest);
}

/* ajouter un moyen pour se balader
dans la ligne qu'on est en trqin d'ecrire
dans le trminal en utilisant les fleches*/
void	ft_heredoc(char *str, t_struct *repo, t_info *info)
{
	int		fd;
	char	*line;

	repo->i_heredoc = 1;
	fd = open("/tmp/heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_put_str_error("Minishell: /tmp/heredoc.txt: ",strerror(errno), NULL, NULL);
		// dup2(info->saved_stderr, STDOUT_FILENO);
		// printf("Minishell: %s: %s\n", "/tmp/heredoc.txt", strerror(errno));
		return ;
	}
	while (1)
	{
		write(info->saved_stdout, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(str, line, ft_strlen(str) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (ft_verif_dollar(line))
			line = ft_expand_heredoc(info, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open("/tmp/heredoc.txt", O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_put_str_error("Minishell: /tmp/heredoc.txt: ",strerror(errno), NULL, NULL);
		// dup2(info->saved_stderr, STDOUT_FILENO);
		// printf("Minishell: %s: %s\n", "/tmp/heredoc.txt", strerror(errno));
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_put_str_error("Minishell: /tmp/heredoc.txt: ", strerror(errno), NULL, NULL);
		// dup2(info->saved_stderr, STDOUT_FILENO);
		// printf("Minishell: %s: %s\n", "/tmp/heredoc.txt", strerror(errno));
		close(fd);
		return ;
	}
	close(fd);
}
