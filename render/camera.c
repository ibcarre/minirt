/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:29:29 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/24 17:27:26 by ibtihal          ###   ########.fr       */
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
	// view_z = - 1;
	// view_w = tan((cam->fov * M_PI/180.0)) / 2;
	// view_h = view_w * (double)HEIGHT/(double)WIDTH;
	// vp->vport = vec_init(view_w, -view_h, view_z);
	view_w = 5.0;
	view_h = view_w * (double)HEIGHT/(double)WIDTH;
	// view_z = - view_w/(2 * (double)tan((double)cam->fov / 2 * M_PI/180));
	view_z = view_w / tan(((double)cam->fov * M_PI/180)/2);
	printf("Focal length : %f\n", view_z);
	vp->vport = vec_init(view_w, -view_h, - view_z);
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
