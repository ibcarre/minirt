/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 18:48:46 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sp 0,-50.5,-100 100 10,0,255

#include "../includes/minirt.h"

void	shading(t_shading *shader, t_vars mlx, t_hit point)
{
	shader->intensity = ft_clamp
		(dot_product(vec_normalize(vec_add_vec(mlx.first->pos,
						point.closest_pt, MINUS)), point.normal), 0, 1)
		* INTENSITE;
	shader->intensity = shader->intensity
		/ vec_length_squared(vec_add_vec(mlx.first->pos,
				point.closest_pt, MINUS));
	shader->lumcol.x = mlx.first->col.x
		* mlx.first->light->ratio * shader->intensity * point.col.x;
	shader->lumcol.y = mlx.first->col.y
		* mlx.first->light->ratio * shader->intensity * point.col.y;
	shader->lumcol.z = mlx.first->col.z
		* mlx.first->light->ratio * shader->intensity * point.col.z;
	shader->col = vec_add_vec(shader->lumcol, shader->col, ADD);
}

t_color	check_lights(t_ray ray, t_vars mlx, t_hit point)
{
	t_hit		shadow;
	double		length;
	t_obj		*first;
	t_shading	shader;

	shader.col = vec_init(0, 0, 0);
	first = mlx.first;
	while (mlx.first)
	{
		if (mlx.first->type == LIGHT)
		{
			ray.direction = vec_add_vec(mlx.first->pos, ray.origin, MINUS);
			length = vec_length_squared(ray.direction);
			ray.direction = vec_normalize(ray.direction);
			check_shadow(ray, first, &shadow, length);
			if (!(shadow.hit))
				shading(&shader, mlx, point);
		}
		mlx.first = mlx.first->next;
	}
	shader.lumcol = col_mul2(mlx.am_light->col, mlx.am_light->amlight->ratio);
	shader.col = vec_add_vec(shader.lumcol, shader.col, ADD);
	shader.col = col_mul_vec(point.col, shader.col);
	return (col_div(shader.col, 255));
}

t_color	check_meshes(t_ray ray, t_vars mlx)
{
	t_color	col;
	t_hit	point;
	t_color	lumcol;

	loop_objects(ray, mlx.first, &point);
	col = col_mul(mlx.am_light->col, 0.8);
	if (point.hit)
	{
		ray.origin = vec_add_vec(point.closest_pt,
				vec_mul(point.normal, 0.0001), ADD);
		lumcol = check_lights(ray, mlx, point);
		return (lumcol);
	}
	return (col);
}

void	show_img(t_color col, t_global *global, t_pos xy)
{
	int	i;

	col.x = (int)ft_clamp((col.x / SAMPLES), 0, 255);
	col.y = (int)ft_clamp((col.y / SAMPLES), 0, 255);
	col.z = (int)ft_clamp((col.z / SAMPLES), 0, 255);
	i = create_trgb(0, col.x, col.y, col.z);
	pthread_mutex_lock(&(global->mutex));
	my_mlx_pixel_put(global->img, xy.y, xy.x, i);
	pthread_mutex_unlock(&(global->mutex));
}

void	ray_color(t_ray ray, t_pos px, t_pos xy, t_global *global)
{
	t_color		col;
	t_obj		*camera;
	int			i;
	t_viewport	*vp;
	double		rand;

	i = 0;
	camera = global->mlx.camera;
	vp = camera->camera->viewport;
	col = col_init(0, 0, 0);
	ray.origin = global->mlx.camera->pos;
	while (i < SAMPLES)
	{
		rand = xy.x + (myrand(px.y + i) - 0.5);
		px = vec_add_vec(vp->pixel_top_left,
				vec_mul(vp->pixel_delta_u, rand), ADD);
		rand = xy.y + (myrand(px.x + i) - 0.5);
		px = vec_add_vec(px, vec_mul(vp->pixel_delta_v, rand), ADD);
		ray.direction = vec_normalize(vec_add_vec(px,
					global->mlx.camera->pos, MINUS));
		col = col_add_col(check_meshes(ray, global->mlx), col);
		i++;
	}
	show_img(col, global, xy);
	return ;
}
