/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 23:19:10 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/24 18:31:30 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_obj_type(t_obj *obj)
{
	if (!obj)
		return ;
	if (obj->amlight)
		free(obj->amlight);
	if (obj->camera)
		free(obj->camera);
	if (obj->light)
		free(obj->amlight);
	if (obj->light)
		free(obj->light);
	if (obj->sphere)
		free(obj->sphere);
	if (obj->plane)
		free(obj->plane);
	if (obj->cylinder)
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