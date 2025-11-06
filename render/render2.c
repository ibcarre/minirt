/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 18:48:57 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sp 0,-50.5,-100 100 10,0,255

#include "../includes/minirt.h"

t_hit	*get_point(t_hit *point, t_obj *first, t_ray ray, t_cylhit p)
{
	if (point->hit == 0 || point->point < point->closest_pt.z)
	{
		point->type = first->type;
		point->closest_pt.z = point->point;
		point->col = first->col;
		point->hit = 1;
		if (point->type == CYLINDER)
			point->cyl_point = p;
		get_normal(first, point, ray);
	}
	point->point = -1;
	return (point);
}

t_hit	loop_objects(t_ray ray, t_obj *first, t_hit *point)
{
	t_cylhit	p;

	point->hit = 0;
	point->closest_pt.z = -1;
	point->point = -1;
	while (first)
	{
		if (first->type == SPHERE)
			point->point = hits_sphere(ray, first);
		else if (first->type == PLANE)
			point->point = hits_plane(ray, first);
		else if (first->type == CYLINDER)
		{
			p = hits_cylinder(ray, first);
			point->point = p.t;
		}
		if (point->point >= 0)
			point = get_point(point, first, ray, p);
		first = first->next;
	}
	point->closest_pt = vec_add_vec
		(ray.origin, vec_mul(ray.direction, point->closest_pt.z), ADD);
	return (*point);
}

t_hit	check_shadow(t_ray ray, t_obj *first, t_hit *shadow, double length)
{
	double	length_hit;
	t_hit	point;

	shadow->hit = 0;
	loop_objects(ray, first, &point);
	if (point.hit)
	{
		length_hit = vec_length_squared
			(vec_add_vec(point.closest_pt, ray.origin, MINUS));
		if (length_hit < length + 1e-6)
		{
			shadow->hit = 1;
			return (*shadow);
		}
	}
	return (*shadow);
}
