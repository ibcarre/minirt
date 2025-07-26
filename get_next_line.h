/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:42:15 by ibaaziz           #+#    #+#             */
/*   Updated: 2024/12/06 11:59:29 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *str);
int		check_n(char *str);
char	*get_next_line(int fd);
char	*ft_strrdup(char **line);
char	*ft_half(char **line, int i);
char	*ft_trim(char **line, int i);
char	*ft_realloc_rd(char **line, int fd, int *rd);
char	*get_next_line(int fd);

#endif
