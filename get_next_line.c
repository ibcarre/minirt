/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:27:25 by ibaaziz           #+#    #+#             */
/*   Updated: 2024/12/15 13:34:34 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_half(char **line, int i)
{
	char	*nl;
	int		j;

	nl = malloc(ft_strlen(*line) - i);
	if (!nl)
		return (NULL);
	j = 0;
	i++;
	while ((*line)[i])
	{
		nl[j] = (*line)[i];
		j++;
		i++;
	}
	nl[j] = 0;
	free(*line);
	return (nl);
}

char	*ft_trim(char **line, int i)
{
	char	*str;
	int		j;

	str = malloc(i + 2);
	j = 0;
	while (j <= i)
	{
		str[j] = (*line)[j];
		j++;
	}
	str[j] = 0;
	if (ft_strlen(*line) - i <= 1)
	{
		free(*line);
		*line = NULL;
	}
	else
	{
		*line = ft_half(line, i);
		if (!*line)
			return (NULL);
	}
	return (str);
}

char	*ft_realloc_rd(char **line, int fd, int *rd)
{
	char	*str;
	int		i;

	if (!*line)
	{
		*line = malloc(BUFFER_SIZE + 1);
		if (!*line)
			return (NULL);
		*rd = read(fd, *line, BUFFER_SIZE);
		if (*rd <= 0)
			return (free(*line), NULL);
		return ((*line)[*rd] = 0, *line);
	}
	str = malloc(ft_strlen(*line) + BUFFER_SIZE + 1);
	i = 0;
	while ((*line)[i])
	{
		str[i] = (*line)[i];
		i++;
	}
	*rd = read(fd, &str[i], BUFFER_SIZE);
	str[i + *rd] = 0;
	free(*line);
	return (str);
}

char	*get_next_line(int fd)
{
	int			rd;
	static char	*line;

	rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || rd < 0)
		return (NULL);
	line = ft_realloc_rd(&line, fd, &rd);
	if (!line)
		return (NULL);
	while (rd > 0 || check_n(line) != -1)
	{
		if (check_n(line) != -1)
			return (ft_trim(&line, check_n(line)));
		line = ft_realloc_rd(&line, fd, &rd);
	}
	if (rd < 0)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	return (ft_strrdup(&line));
}
