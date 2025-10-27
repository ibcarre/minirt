/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:29:29 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/27 16:40:12 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"
#include "../includes/minirt.h"

// t_viewport	*viewport_init(t_camera *cam)
// {
// 	t_viewport	*vp;
// 	double		view_h;
// 	double		view_w;
// 	double		view_z;
// 	double		angle;
// 	t_pos		view_dir;

// 	vp = cam->viewport;
// 	// view_z = - 1;
// 	// view_w = tan((cam->fov * M_PI/180.0)) / 2;
// 	// view_h = view_w * (double)HEIGHT/(double)WIDTH;
// 	// vp->vport = vec_init(view_w, -view_h, view_z);
// 	view_w = 5.0;
// 	view_h = view_w * (double)HEIGHT/(double)WIDTH;
// 	// view_z = - view_w/(2 * (double)tan((double)cam->fov / 2 * M_PI/180));
// 	angle = (double)cam->fov * M_PI/180;
// 	angle = angle/2;
// 	view_z = view_w / tan(angle);
// 	view_z = view_z / 2;
// 	//vp->vport = vec_init(view_w, -view_h, view_z);
// 	return (vp);
// }

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
	//t_viewport	*vp;
	t_pos		v_up;
	t_pos		u, v, w;
	double		angle;
	double		foc_length;
	double		viewport_width, viewport_height;

	camera = get_camera(camera);
	v_up = vec_init(0,1,0);
	//foc_length = vec_length(vec_add_vec(camera->pos, camera->camera->orientation, MINUS));
	foc_length = vec_length(camera->camera->orientation);
	angle = (double)camera->camera->fov * M_PI/180;
	angle = angle/2;
	viewport_width = 2 * tan(angle) * foc_length;
	viewport_height = viewport_width * (double)HEIGHT/(double)WIDTH;
	printf("Focal length : %f\n", foc_length);
	//w = vec_normalize(vec_add_vec(camera->pos, camera->camera->orientation, MINUS));
	//w = vec_normalize(vec_add_vec(camera->pos, camera->camera->orientation, MINUS));
	w = vec_mul(camera->camera->orientation, -1);
	//w = vec_normalize(vec_add_vec(vec_mul_vec(camera->camera->orientation, camera->pos), camera->pos, MINUS));
	u = vec_normalize(cross(v_up, w));
	v = vec_normalize(cross(w, u));
	print_vec("WWW ", w);
	print_vec("UUU ", u);
	print_vec("VVV ", v);
	camera->camera->viewport->vport_u = vec_mul(u, viewport_width);
	camera->camera->viewport->vport_v = vec_mul(v, -viewport_height);
	camera->camera->viewport->pixel_delta_u = vec_div(camera->camera->viewport->vport_u, WIDTH);
	camera->camera->viewport->pixel_delta_v = vec_div(camera->camera->viewport->vport_v, HEIGHT);
	camera->camera->viewport->pixel_top_left = vec_add_vec(camera->pos, vec_mul(w, foc_length), MINUS);
	print_vec("z pixel ", camera->camera->viewport->pixel_top_left);
	camera->camera->viewport->pixel_top_left = vec_add_vec(camera->camera->viewport->pixel_top_left, vec_div(camera->camera->viewport->vport_u, 2), MINUS);
	camera->camera->viewport->pixel_top_left = vec_add_vec(camera->camera->viewport->pixel_top_left, vec_div(camera->camera->viewport->vport_v, 2), MINUS);
	camera->camera->viewport->pixel_top_left = vec_add_vec(camera->camera->viewport->pixel_top_left, vec_add_vec(camera->camera->viewport->pixel_delta_u, camera->camera->viewport->pixel_delta_v, ADD), ADD); //viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	print_vec("z pixel ", camera->camera->viewport->pixel_top_left);
	//camera->camera->viewport = vp;
	return (camera);
}
