/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/02 18:12:18 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sp 0,-50.5,-100 100 10,0,255

#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_data *data, int height, int width, int color)
{
	char	*dst;

	dst = data->addr + (height * data->line_length + width * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close_window(t_vars *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free_objs(mlx->first);
	exit(0);
}

int	handle_key(int keycode, t_vars *mlx)
{
	if (keycode == XK_Escape)
		close_window(mlx);
	return (0);
}

double	my_sq(double x)
{
	return (x * x);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	hits_sphere(t_ray ray, t_obj *first)
{
	t_pos	or_to_oc; //rayon to centre
	double	a;
	double	h;
	double	c;
	double	delta;

	or_to_oc = vec_add_vec(first->pos, ray.origin, MINUS);
	a = vec_length(ray.direction) * vec_length(ray.direction);//dot_product(ray.direction, ray.direction);
	h =  dot_product(ray.direction, or_to_oc); //-2 * dot_product(ray.direction, or_to_oc);
	c = my_sq(vec_length(or_to_oc)) - my_sq(first->sphere->rayon);//dot_product(cr, cr) - mlx.first->sphere->rayon * mlx.first->sphere->rayon;
	delta = h * h - a * c;
	if (delta >= 0)
	{
		delta = (h - sqrt(delta)) / (a);
		if (delta < 0)
		{
			delta = (h + sqrt(h * h - a * c)) / a;
			return (delta);
		}
		return (delta); // moins pour obtenir la solution la plus proche de la caméra, return negatif quand on est dans la sphère (forcément...)
	}
	return (-1);
}

t_pos	get_normal(t_obj *first, t_hit *point, t_ray ray)
{
	t_pos	normal;
	t_pos	t_point;

	t_point = vec_add_vec(ray.origin, vec_mul(ray.direction, point->closest_pt.z), ADD);
	if (!first)
		return (vec_init(0, 0, 0));
	else if (first->type == SPHERE)
		normal = vec_normalize(vec_add_vec(t_point, first->pos, MINUS));
	else if (first->type == PLANE)
			normal = first->plane->normal;
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

// double	hits_cylinder(t_ray ray, t_obj *obj)
// {

// 	return (-1);
// }

t_hit	loop_objects(t_ray ray, t_obj *first, t_hit *point)
{
	point->hit = 0;
	point->closest_pt.z = -1;
	point->point = -1;
	while (first)
	{
		if (first->type == SPHERE)
			point->point = hits_sphere(ray, first);
		else if (first->type == PLANE)
			point->point = hits_plane(ray, first);
		// else if (first->type == CYLINDER)
		//  	point->point = hits_cylinder(ray, first);
		if (point->point >= 0)
		{
			if (point->hit == 0 || point->point < point->closest_pt.z)
			{
				point->type = first->type;
				point->closest_pt.z = point->point;
				point->col = first->col;
				point->hit = 1;
				get_normal(first, point, ray);
			}
			point->point = -1;
		}
		first = first->next;
	}
	point->closest_pt = vec_add_vec(ray.origin, vec_mul(ray.direction, point->closest_pt.z), ADD);
	return (*point);
}


t_hit	check_shadow(t_ray ray, t_obj *first, t_hit *shadow, double	length)
{
	double	length_hit;
	t_hit	point;

	shadow->hit = 0;
	loop_objects(ray, first, &point);
	if (point.hit)
	{
		length_hit = vec_length_squared(vec_add_vec(point.closest_pt, ray.origin, MINUS));
		if (length_hit < length + 1e-6)
		{
			shadow->hit = 1;
			return (*shadow);
		}
	}
	return (*shadow);
}

t_color	check_lights(t_ray ray, t_vars mlx, t_hit point)
{
	t_hit	shadow;
	t_pos	col;
	t_pos	lumcol;
	t_color	res;
	double	length;
	double	intensite;
	t_obj	*first;

	col = vec_init(0,0,0);
	first = mlx.first;
	while(mlx.first)
	{
		if (mlx.first->type == LIGHT)
		{
			ray.direction = vec_add_vec(mlx.first->pos, ray.origin, MINUS);
			length = vec_length_squared(ray.direction);
			ray.direction = vec_normalize(ray.direction);
			check_shadow(ray, first, &shadow, length);
			if (!(shadow.hit))
			{
				intensite = ft_clamp(dot_product(vec_normalize(vec_add_vec(mlx.first->pos, point.closest_pt, MINUS)), point.normal), 0, 1) * INTENSITE;
				intensite = intensite / vec_length_squared(vec_add_vec(mlx.first->pos, point.closest_pt, MINUS));
				lumcol.x = mlx.first->col.x * mlx.first->light->ratio * intensite * point.col.x;
				lumcol.y = mlx.first->col.y * mlx.first->light->ratio * intensite * point.col.y;
				lumcol.z = mlx.first->col.z * mlx.first->light->ratio * intensite * point.col.z;
				col = vec_add_vec(lumcol, col, ADD);
			}
		}
		mlx.first = mlx.first->next;
	}
	lumcol.x = mlx.am_light->col.x * mlx.am_light->amlight->ratio;
	lumcol.y = mlx.am_light->col.y * mlx.am_light->amlight->ratio;
	lumcol.z = mlx.am_light->col.z * mlx.am_light->amlight->ratio;
	col = vec_add_vec(lumcol, col, ADD);
	col.x = col.x * point.col.x;
	col.y = col.y * point.col.y;
	col.z = col.z * point.col.z;
	res.x = col.x / 255;
	res.y = col.y / 255;
	res.z = col.z / 255;
	return (res);
}

t_color	check_meshes(t_ray ray, t_vars mlx)
{
	t_color col;
	t_hit	point;
	t_color	lumcol;

	loop_objects(ray, mlx.first, &point);
	col = col_mul(mlx.am_light->col, 0.8);
	if (point.hit)
	{
		ray.origin = vec_add_vec(point.closest_pt, vec_mul(point.normal, 0.0001), ADD);
		lumcol = check_lights(ray, mlx, point); //col_mul(col_init(0,0,255), intensite * 0.5);
		return(lumcol);
	}
	return (col);
}

void	ray_color(t_ray ray, t_pos px, t_pos xy, t_global *global) //t_vars mlx, t_data *img, 
{
	t_color		col;
	t_obj	*camera;
	int	i;
	t_viewport *vp;
	double rand;

	i = 0;
	camera = global->mlx.camera;
	vp = camera->camera->viewport;
	col = col_init(0,0,0);
	ray.origin = global->mlx.camera->pos;
	while (i < SAMPLES)
	{
		rand = xy.x + (myrand(px.y + i) - 0.5);
		px = vec_add_vec(vp->pixel_top_left, vec_mul(vp->pixel_delta_u, rand), ADD);
		rand = xy.y + (myrand(px.x + i) - 0.5);
		px = vec_add_vec(px, vec_mul(vp->pixel_delta_v, rand), ADD);
		ray.direction = vec_normalize(vec_add_vec(px, global->mlx.camera->pos, MINUS)); //vecteur qui part de la camera vers le pixel voulu
		col = col_add_col(check_meshes(ray, global->mlx), col);
		i++;
	}
	col.x = (int)ft_clamp((col.x/SAMPLES), 0, 255);
	col.y = (int)ft_clamp((col.y/SAMPLES), 0, 255);
	col.z = (int)ft_clamp((col.z/SAMPLES), 0, 255);
	i = create_trgb(0, col.x, col.y, col.z);
	pthread_mutex_lock(&(global->mutex));
	my_mlx_pixel_put(global->img, xy.y, xy.x, i);
	pthread_mutex_unlock(&(global->mutex));
	return ;
}

void	*routine(void *param)
{
	t_global	*global;
	t_pos		xy;
	t_pos		pixel;
	t_ray		ray;

	global = (t_global *) param;
	pthread_mutex_lock(&(global->mutex));
	xy.y = global->img->y;
	pthread_mutex_unlock(&(global->mutex));
	while (xy.y < HEIGHT)
	{
		xy.x = 0;
		while (xy.x < WIDTH)
		{
			pixel = vec_add_vec(global->vp->pixel_top_left, vec_mul(global->vp->pixel_delta_u, xy.x), ADD);
			pixel = vec_add_vec(pixel, vec_mul(global->vp->pixel_delta_v, xy.y), ADD);
			ray_color(ray, pixel, xy, global);
			xy.x = xy.x + 1;
		}
		pthread_mutex_lock(&(global->mutex));
		global->img->y = global->img->y + 1;
		xy.y = global->img->y;
		pthread_mutex_unlock(&(global->mutex));
		loading(xy.y);
	}
	return (NULL);
}


void	render_image(t_vars mlx, t_data *img)
{

	pthread_t	threads[CORES];
	t_global	glob;
	int	i;

	img->y = 0;
	i = 0;
	mlx.am_light = get_amlight(mlx);
	mlx.camera = camera_setup(mlx.first);
	glob.mlx = mlx;
	glob.img = img;
	glob.img->y = 0;
	glob.vp = mlx.camera->camera->viewport;
	pthread_mutex_init(&(glob.mutex), NULL);
	while (i < CORES)
	{
		pthread_create(&(threads[i]), NULL, routine, &glob);
		i++;
	}
	i = 0;
	while (i < CORES)
	{
		pthread_join((threads[i]), NULL);
		i++;
	}
}

void	render(t_obj *first)
{
	t_vars mlx;
	t_data	img;

	mlx.first = first ;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "blender");
	img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_image(mlx, &img);
	write(1, "\rRENDERING 100%", 15);
	printf("\n");
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 17, 1L<<0, &close_window, &mlx);
	mlx_key_hook(mlx.win, &handle_key, &mlx);
	mlx_loop(mlx.mlx);
}
