/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:18:32 by ibaaziz           #+#    #+#             */
/*   Updated: 2025/08/24 18:31:19 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strrdup(char **line)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(ft_strlen(*line) + 1);
	while ((*line)[i])
	{
		str[i] = (*line)[i];
		i++;
	}
	str[i] = 0;
	free(*line);
	*line = NULL;
	return (str);
}
