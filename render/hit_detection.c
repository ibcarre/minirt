/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:19:43 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 19:19:23 by ibtihal          ###   ########.fr       */
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
	else if (first->type == CYLINDER)
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

double	check_caps(t_obj *obj, t_pos top, t_pos bot, t_ray ray)
{
	t_pos	axe;
	double	tc;
	double	tc2;
	t_pos	ic;

	axe = vec_normalize(obj->cylinder->normal);
	tc = dot_product(axe, vec_add_vec(top, ray.origin, MINUS))
		/ dot_product(axe, ray.direction);
	ic = vec_add_vec(ray.origin, vec_mul(ray.direction, tc), ADD);
	if (vec_length(vec_add_vec(ic, top, MINUS)) > obj->cylinder->rayon)
		tc = -1 ;
	tc2 = dot_product(axe, vec_add_vec(bot, ray.origin, MINUS))
		/ dot_product(axe, ray.direction);
	ic = vec_add_vec(ray.origin, vec_mul(ray.direction, tc2), ADD);
	if (vec_length(vec_add_vec(ic, bot, MINUS)) > obj->cylinder->rayon)
		tc2 = -1;
	if (tc < 0)
		return (tc2);
	return (tc);
}

t_cylhit	hits_cylinder(t_ray ray, t_obj *obj)
{
	t_cylhit	p;
	t_pos center = obj->pos;
	t_pos axe = vec_normalize(obj->cylinder->normal);
	t_pos top = vec_add_vec(center, vec_mul(axe, obj->cylinder->height * 0.5 ), ADD);
	t_pos bot = vec_add_vec(center, vec_mul(axe, obj->cylinder->height * 0.5 ), MINUS);
	t_pos rdXaxe = cross(ray.direction, axe);
	double r2 = obj->cylinder->rayon * obj->cylinder->rayon;
	double aa = dot_product(axe, axe);
	double ra = dot_product(rdXaxe, rdXaxe);
	t_pos b0 = vec_add_vec(bot, ray.origin, MINUS);
	double B = dot_product(rdXaxe, cross(b0, axe));
	double d = dot_product(b0, rdXaxe);
	double D = ra * r2 - aa * d * d;
	double	t;

	t = check_caps(obj, top, bot, ray);
	if (D < 0) {
		p.t = t;
		p.endcap = 1;
		p.body = 0;
		return (p);
	}
	D = sqrt(D);
	double t2 = (B - D) / ra;
	if (t2 < 0) {
		t2 = (B + D) / ra;
	}
	if (t2 < 0){
		p.t = t;
		p.endcap = 1;
		p.body = 0;
		return (p);
	}
	t_pos I = vec_add_vec(ray.origin, vec_mul(ray.direction, t2), ADD);
	double l = dot_product(axe, vec_add_vec(I, bot, MINUS));
	if (0 < l && l < obj->cylinder->height)
	{
		if (t < 0 || t2 < t)
		{
			p.t = t2;
			p.endcap = 0;
			p.body = 1;
			return (p);
		}
	}
	p.t = t;
	p.endcap = 1;
	p.body = 0;
	return (p);	
}
