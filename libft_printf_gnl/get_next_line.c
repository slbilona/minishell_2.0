/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <ilselbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:57:09 by ilselbon          #+#    #+#             */
/*   Updated: 2023/04/04 21:09:37 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ligne;

	if (fd < 0 && str != NULL)
		return (free(str), NULL);
	if (fd < 0)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	ligne = ft_copy(str);
	if (!ligne)
		return (NULL);
	str = ft_free_str(str);
	return (ligne);
}

char	*ft_str(void)
{
	char	*str;

	str = malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*ft_cat(char *str, char *buf)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
	{
		str = ft_str();
		if (!str)
			return (NULL);
	}
	if (buf[0] == 0 && str[0] == 0)
		return (ft_free(str));
	new = malloc(sizeof(char) * (ft_strlen_gnl(str) + ft_strlen_gnl(buf) + 1));
	if (!new)
		return (NULL);
	while (str[j])
		new[i++] = str[j++];
	j = 0;
	while (buf[j])
		new[i++] = buf[j++];
	new[i] = 0;
	free(str);
	return (new);
}

char	*ft_copy(const char *str)
{
	char	*ligne;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ligne = malloc(sizeof(char) * (ft_strlen_gnl(str) + 2));
	if (!ligne)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		ligne[i] = str[i];
		i++;
	}
	ligne[i] = 0;
	return (ligne);
}

char	*ft_read(int fd, char *str)
{
	char	*buf;
	int		i;
	int		buffer;

	i = 1;
	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = BUFFER_SIZE;
	if (BUFFER_SIZE == 1)
		buffer = 10;
	buf = malloc(sizeof(char) * (buffer + 1));
	if (!buf)
		return (NULL);
	while (i && !ft_strchr_gnl(str, '\n'))
	{
		i = read(fd, buf, buffer);
		if (i < 0)
			return (ft_free(buf));
		buf[i] = 0;
		str = ft_cat(str, buf);
		if (!str)
			return (ft_free(buf));
	}
	free(buf);
	return (str);
}
