/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:35 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 15:43:01 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_obj	*fill_cylinder(char *line, t_obj **obj)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	i = 1;
	(*obj)->cylinder = malloc(sizeof(t_cylinder));
	if (!fill_pos(*obj, &line) || !((*obj)->cylinder))
		return (free(*obj), *obj = NULL);
	if (!fill_or(&((*obj)->cylinder->normal), &line))
		return (free_objs(*obj), *obj = NULL);
	(*obj)->cylinder->rayon = ft_clamp(ft_atof(&line, &i), 0, INT_MAX) / 2;
	(*obj)->cylinder->height = ft_clamp(ft_atof(&line, &i), 0, INT_MAX);
	if (!fill_col(*obj, &line) || !i)
	{
		free_objs(*obj);
		(*obj) = NULL;
	}
	return (*obj);
}

void	fill_obj(char *line, t_obj **last)
{
	if (!*last)
		return ;
	if ((*last)->type == A_LIGHT)
		fill_alight(line, last);
	else if ((*last)->type == SPHERE)
		fill_sphere(line, last);
	else if ((*last)->type == LIGHT)
		fill_light(line, last);
	else if ((*last)->type == CAMERA)
		fill_camera(line, last);
	else if ((*last)->type == PLANE)
		fill_plane(line, last);
	else if ((*last)->type == CYLINDER)
		fill_cylinder(line, last);
	return ;
}
