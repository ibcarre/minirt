/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:13:41 by ibtihal           #+#    #+#             */
/*   Updated: 2025/07/26 22:34:41 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_obj	*init_obj()
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
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

t_obj	*parsing(int fd)
{
	char	*line;
	t_obj	*first;

	first = init_obj();
	print_obj_param(first);
	line = get_next_line(fd);
}