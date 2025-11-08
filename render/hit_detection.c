/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:19:43 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/08 12:28:34 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	hits_sphere(t_ray ray, t_obj *first)
{
	t_pos	or_to_oc;
	double	a;
	double	h;
	double	c;
	double	delta;

	or_to_oc = vec_add_vec(first->pos, ray.origin, MINUS);
	a = vec_length(ray.direction) * vec_length(ray.direction);
	h = dot_product(ray.direction, or_to_oc);
	c = my_sq(vec_length(or_to_oc)) - my_sq(first->sphere->rayon);
	delta = h * h - a * c;
	if (delta >= 0)
	{
		delta = (h - sqrt(delta)) / (a);
		if (delta < 0)
		{
			delta = (h + sqrt(h * h - a * c)) / a;
			return (delta);
		}
		return (delta);
	}
	return (-1);
}

t_pos	get_cyl_norm(t_pos t_point, t_obj *first)
{
	t_pos	c_hit;
	double	proj;
	t_pos	proj_p;

	c_hit = vec_add_vec(t_point, first->pos, MINUS);
	proj = dot_product(vec_normalize(first->cylinder->normal), c_hit);
	proj_p = vec_add_vec(first->pos,
			vec_mul(vec_normalize(first->cylinder->normal), proj), ADD);
	return (vec_normalize(vec_add_vec(t_point, proj_p, MINUS)));
}

t_pos	get_normal(t_obj *first, t_hit *point, t_ray ray)
{
	t_pos	normal;
	t_pos	t_point;

	t_point = vec_add_vec(ray.origin,
			vec_mul(ray.direction, point->closest_pt.z), ADD);
	if (!first)
		return (vec_init(0, 0, 0));
	else if (first->type == SPHERE)
		normal = vec_normalize(vec_add_vec(t_point, first->pos, MINUS));
	else if (first->type == PLANE)
		normal = vec_normalize(first->plane->normal);
	else
	{
		if (point->cyl_point.endcap)
			normal = vec_normalize(first->cylinder->normal);
		else
			normal = get_cyl_norm(t_point, first);
	}
	if (dot_product(ray.direction, normal) > 0)
		normal = vec_init(-normal.x, -normal.y, -normal.z);
	point->normal = normal;
	return (normal);
}

double	hits_plane(t_ray ray, t_obj *first)
{
	double	denom;
	t_pos	point;
	double	t;

	denom = dot_product(first->plane->normal, ray.direction);
	if (abs_f(denom) > 1e-6)
	{
		point = vec_add_vec(first->pos, ray.origin, MINUS);
		t = dot_product(point, first->plane->normal) / denom;
		if (t > 1e-6)
			return (t);
		return (-1);
	}
	return (-1);
}
