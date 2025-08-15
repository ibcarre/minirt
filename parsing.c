/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:13:41 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/14 19:49:49 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*init_obj()
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->next = NULL;
	obj->amlight = NULL;
	obj->camera = NULL;
	obj->light = NULL;
	obj->sphere = NULL;
	obj->plane = NULL;
	obj->cylinder = NULL;
	obj->col.x = 0;
	obj->col.y = 0;
	obj->col.z = 0;
	obj->pos.x = 0;
	obj->pos.y = 0;
	obj->pos.z = 0;
	return (obj);
}

//check chaque valeur si valeur mauvaise print warning sur terminal et mise default value

t_obj	*check_type(char *line, t_obj *obj)
{
	int	i;

	if (!obj)
		return (NULL);
	i = 0;
	if (line[i] == 'a' || line[i] == 'A')
		(obj)->type = A_LIGHT;
	else if ((line[i] == 'c' || line[i] == 'C') && line[i + 1] != 'y')
		(obj)->type = CAMERA;
	else if (line[i] == 'l' || line[i] == 'L')
		(obj)->type = LIGHT;
	else if ((line[i] == 's' || line[i] == 'S') && line[i + 1] == 'p')
		(obj)->type = SPHERE;
	else if ((line[i] == 'p' || line[i] == 'P') && line[i + 1] == 'l')
		(obj)->type = PLANE;
	else if ((line[i] == 'c' || line[i] == 'C') && line[i + 1] == 'y')
		(obj)->type = CYLINDER;
	else
	{
		free(obj);
		printf("Wrong type\n");
		return (NULL);
	}
	return (obj);
}

t_obj	*get_obj(char *line, t_obj *first)
{
	t_obj	*last;
	t_obj	*obj;

	line = skip_spaces(line);
	last = init_obj();
	last = check_type(line, last);
	fill_obj(line, &last);
	if (!last)
	{
		free_objs(first);
		return (NULL);
	}
	if (!first)
		return (last);
	obj = get_last(first);
	obj->next = last;
	return (first);
}

t_obj	*parsing(int fd)
{
	char	*line;
	t_obj	*first;

	first = NULL;
	line = get_next_line(fd);
	while (line)
	{
		first = get_obj(line, first);
		free(line);
		if (!first)
			return (NULL);
		line = get_next_line(fd);
		while (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	free(line);
	return (first);
}
