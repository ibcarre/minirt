/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:19:10 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/22 11:08:47 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_obj_type(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->amlight)
		free(obj->amlight);
	else if (obj->camera)
	{
		if (obj->camera->viewport)
			free(obj->camera->viewport);
		free(obj->camera);
	}
	else if (obj->light)
		free(obj->light);
	else if (obj->sphere)
		free(obj->sphere);
	else if (obj->plane)
		free(obj->plane);
	else if (obj->cylinder)
		free(obj->cylinder);
}

void	free_objs(t_obj *obj)
{
	if (!obj)
		return ;
	if (!(obj->next))
	{
		free_obj_type(obj);
		free(obj);
		return ;
	}
	free_objs(obj->next);
	free_obj_type(obj);
	free(obj);
}

double	abs_f(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}