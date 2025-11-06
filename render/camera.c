/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:29:29 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 13:19:19 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

t_axis	get_local_orientation(t_pos	or)
{
	t_pos	v_up;
	t_axis	new;

	or = vec_normalize(or);
	print_vec("ORIENTATION ", or);
	if (or.y != 1 && or.y != -1)
		v_up = vec_init(0, 1, 0);
	else
		v_up = vec_init(0, 0, 1);
	new.w = vec_mul(or, -1);
	new.u = vec_normalize(cross(v_up, new.w));
	new.v = vec_normalize(cross(new.w, new.u));
	return (new);
}

void	setup_vport(t_axis axis, double vwidth, double vheight, t_obj *camera)
{
	double	foc_length;

	foc_length = vec_length(camera->camera->orientation);
	camera->camera->viewport->vport_u = vec_mul(axis.u, vwidth);
	camera->camera->viewport->vport_v = vec_mul(axis.v, -vheight);
	camera->camera->viewport->pixel_delta_u
		= vec_div(camera->camera->viewport->vport_u, WIDTH);
	camera->camera->viewport->pixel_delta_v
		= vec_div(camera->camera->viewport->vport_v, HEIGHT);
	camera->camera->viewport->pixel_top_left
		= vec_add_vec(camera->pos, vec_mul(axis.w, foc_length), MINUS);
	camera->camera->viewport->pixel_top_left
		= vec_add_vec(camera->camera->viewport->pixel_top_left,
			vec_div(camera->camera->viewport->vport_u, 2), MINUS);
	camera->camera->viewport->pixel_top_left
		= vec_add_vec(camera->camera->viewport->pixel_top_left,
			vec_div(camera->camera->viewport->vport_v, 2), MINUS);
	camera->camera->viewport->pixel_top_left
		= vec_add_vec(camera->camera->viewport->pixel_top_left,
			vec_add_vec(camera->camera->viewport->pixel_delta_u,
				camera->camera->viewport->pixel_delta_v, ADD), ADD);
	return ;
}

t_obj	*camera_setup(t_obj *camera)
{
	t_axis		axis;
	double		angle;
	double		foc_length;
	double		viewport_width;
	double		viewport_height;

	camera = get_camera(camera);
	camera->camera->orientation = vec_normalize(camera->camera->orientation);
	foc_length = vec_length(camera->camera->orientation);
	angle = (double)camera->camera->fov * M_PI / 180;
	angle = angle / 2;
	viewport_width = 2 * tan(angle) * foc_length;
	viewport_height = viewport_width * (double)HEIGHT / (double)WIDTH;
	printf("Focal length : %f\n", foc_length);
	axis = get_local_orientation(camera->camera->orientation);
	setup_vport(axis, viewport_width, viewport_height, camera);
	return (camera);
}
