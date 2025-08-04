/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:18:16 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/04 16:39:53 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_Alight(char *line)
{
	line[0] = 'a';
	return (1);
}

int	check_camera(char *line)
{
	line[0] = 'a';
	return (1);
}

int	check_cyl(char *line)
{
	line[0] = 'a';
	return (1);
}

int	check_plane(char *line)
{
	line[0] = 'a';
	return (1);
}

int	check_light(char *line)
{
	line[0] = 'a';
	return (1);
}

int	check_sphere(char *line)
{
	line[0] = 'a';
	return (1);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!(line[i]) || line[i] == '\n')
		return (1);
	else if (line[i] == 'A')
		return (check_Alight(&line[i+1]));
	else if (line[i] == 'C')
		return (check_camera(&line[i+1]));
	else if (line[i] == 'L')
		return (check_light(&line[i+1]));
	else if (line[i] == 's' && line[ i + 1] == 'p')
		return (check_sphere(&line[i+1]));
	else if (line[i] == 'p' && line[i + 1] == 'l')
		return (check_plane(&line[i+1]));
	else if (line[i] == 'c' && line[i + 1] == 'y')
		return (check_cyl(&line[i+1]));
	write(2, "Wrong identifier\n", 17);
	return (-1);
}

int	is_correct(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (-1);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (check_line(line) == -1)
				return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}