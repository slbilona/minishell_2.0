/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilselbon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:57:15 by ilselbon          #+#    #+#             */
/*   Updated: 2022/12/07 11:57:17 by ilselbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 111
# endif

# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
int		ft_strlen_gnl(const char *str);
int		ft_strchr_gnl(char *str, char c);
char	*ft_free_str(char *str);
char	*ft_cat(char *str, char *buf);
char	*ft_copy(const char *str);
char	*ft_read(int fd, char *str);
char	*ft_free(char *str);
#endif
