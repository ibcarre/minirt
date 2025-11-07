/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:19:43 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/07 13:13:28 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
	if (tc2 < 0)
		return (tc);
	if (tc < tc2)
		return (tc);
	return (tc2);
}

t_cyl	set_cyl(t_ray ray, t_obj *obj)
{
	t_cyl	cyl;

	cyl.center = obj->pos;
	cyl.axe = vec_normalize(obj->cylinder->normal);
	cyl.top = vec_add_vec(cyl.center,
			vec_mul(cyl.axe, obj->cylinder->height * 0.5), ADD);
	cyl.bot = vec_add_vec(cyl.center,
			vec_mul(cyl.axe, obj->cylinder->height * 0.5), MINUS);
	cyl.rdxaxe = cross(ray.direction, cyl.axe);
	cyl.r2 = obj->cylinder->rayon * obj->cylinder->rayon;
	cyl.aa = dot_product(cyl.axe, cyl.axe);
	cyl.ra = dot_product(cyl.rdxaxe, cyl.rdxaxe);
	cyl.b0 = vec_add_vec(cyl.bot, ray.origin, MINUS);
	cyl.b = dot_product(cyl.rdxaxe, cross(cyl.b0, cyl.axe));
	cyl.d = dot_product(cyl.b0, cyl.rdxaxe);
	cyl.delta = cyl.ra * cyl.r2 - cyl.aa * cyl.d * cyl.d;
	cyl.p.endcap = 0;
	return (cyl);
}

t_cylhit	hits_cylinder(t_ray ray, t_obj *obj)
{
	t_cyl	cyl;
	double	t2;
	t_pos	i;
	double	l;

	cyl = set_cyl(ray, obj);
	cyl.t = check_caps(obj, cyl.top, cyl.bot, ray);
	if (cyl.delta < 0)
		return (cyl.p.t = cyl.t, cyl.p.endcap = 1, cyl.p);
	cyl.delta = sqrt(cyl.delta);
	t2 = (cyl.b - cyl.delta) / cyl.ra;
	if (t2 < 0)
		t2 = (cyl.b + cyl.delta) / cyl.ra;
	if (t2 < 0)
		return (cyl.p.t = cyl.t, cyl.p.endcap = 1, cyl.p);
	i = vec_add_vec(ray.origin, vec_mul(ray.direction, t2), ADD);
	l = dot_product(cyl.axe, vec_add_vec(i, cyl.bot, MINUS));
	if (0 < l && l < obj->cylinder->height)
	{
		if (cyl.t < 0 || t2 < cyl.t)
			return (cyl.p.t = t2, cyl.p);
	}
	return (cyl.p.t = cyl.t, cyl.p.endcap = 1, cyl.p);
}
