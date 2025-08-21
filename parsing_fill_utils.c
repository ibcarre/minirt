/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:49:41 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/20 19:20:23 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_col(t_obj *obj)
{
	if (obj->col.x < 0 || obj->col.y < 0 || obj->col.z < 0)
		printf("COLOR VALUES LOWER THAN 0 CEILED TO 0");
	if (obj->col.x > 255 || obj->col.y > 255 || obj->col.z > 255)
		printf("COLOR VALUES HIGHER THAN 255 FLOORED TO 255");
	if (obj->col.x < 0)
		obj->col.x = 0;
	if (obj->col.y < 0)
		obj->col.y = 0;
	if (obj->col.z < 0)
		obj->col.z = 0;
	if (obj->col.x > 255)
		obj->col.x = 255;
	if (obj->col.y > 255)
		obj->col.y = 255;
	if (obj->col.z > 255)
		obj->col.z = 255;
}

int	fill_col(t_obj *obj, char **line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	*line = skip_spaces(*line);
	while((*line)[i] && !ft_isspace((*line)[i]))
	{
		if ((*line)[i] == ',')
			commas ++;
		i++;
	}
	if (commas != 2)
		return (0);
	(obj)->col.x = ft_atoi(line);
	i = 1;
	(obj)->col.y = ft_atoi(line);
	i = 1;
	(obj)->col.z = ft_atoi(line);
	check_col(obj);
	return (1);
}

int	fill_pos(t_obj *obj, char **line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	*line = skip_spaces(*line);
	while((*line)[i] && !ft_isspace((*line)[i]))
	{
		if ((*line)[i] == ',')
			commas ++;
		i++;
	}
	if (commas != 2)
		return (0);
	(obj)->pos.x = ft_atof(line, &commas);
	i = 1;
	(obj)->pos.y = ft_atof(line, &commas);
	i = 1;
	(obj)->pos.z = ft_atof(line, &commas);
	if (!commas)
		return (0);
	return (1);
}
