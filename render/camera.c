/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:29:29 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/22 02:55:48 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"
#include "../includes/minirt.h"

t_viewport	*viewport_init(t_camera *cam)
{
	t_viewport	*vp;
	double		view_h;
	double		view_w;
	double		view_z;

	vp = cam->viewport;
	view_h = 5.0;
	view_w = (view_h * (double)WIDTH/(double)HEIGHT);
	view_z = - (view_w/(2 * tan((cam->fov * M_PI/180))));
	printf("With this FOC, you have a focal length of %f\n", -view_z);
	vp->vport = vec_init(view_w, -view_h, view_z);
	return (vp);
}

t_obj	*get_camera(t_obj *obj)
{
	while (obj)
	{
		if (obj->type == CAMERA)
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}

t_obj	*camera_setup(t_obj *camera)
{
	t_viewport	*vp;

	camera = get_camera(camera);
	vp = viewport_init(camera->camera);
	vp->pixel_delta.x = camera->camera->viewport->vport.x/(double)WIDTH;
	vp->pixel_delta.y = camera->camera->viewport->vport.y/(double)HEIGHT;
	vp->pixel_top_left.y = camera->pos.y - (camera->camera->viewport->vport.y / 2) + (vp->pixel_delta.y / 2);
	vp->pixel_top_left.x = camera->pos.x - (camera->camera->viewport->vport.x / 2) + (vp->pixel_delta.x / 2);
	vp->pixel_top_left.z = camera->pos.z + camera->camera->viewport->vport.z; // right handed orientation camera faces -z 
	camera->camera->viewport = vp;
	return (camera);
}
