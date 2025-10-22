/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/22 04:55:32 by ibtihal          ###   ########.fr       */
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
	if(keycode == XK_Escape)
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

double	hits_sphere(t_ray ray, t_vars mlx)
{
	t_pos	or_to_oc; //rayon to centre
	double	a;
	double	h;
	double	c;
	double delta;

	or_to_oc = vec_add_vec(mlx.first->pos, ray.origin, MINUS);
	a = vec_length(ray.direction) * vec_length(ray.direction);//dot_product(ray.direction, ray.direction);
	h =  dot_product(ray.direction, or_to_oc); //-2 * dot_product(ray.direction, or_to_oc);
	c = my_sq(vec_length(or_to_oc)) - my_sq(mlx.first->sphere->rayon);//dot_product(cr, cr) - mlx.first->sphere->rayon * mlx.first->sphere->rayon;
	delta = h * h - a * c;
	if (delta >= 0)
	{
		delta = (h - sqrt(delta))/(a);
		if (delta < 0)
		{
			delta = (h + sqrt(h * h - a * c))/a;
			return (delta);
		}
		return (delta); // moins pour obtenir la solution la plus proche de la caméra, return negatif quand on est dans la sphère (forcément...)
	}
	return (-1);
}

t_pos	get_normal(t_vars mlx, t_hit point, t_ray ray)
{
	t_pos	normal;
	t_pos	t_point;

	t_point = vec_add_vec(ray.origin, vec_mul(ray.direction, point.closest_pt.z), ADD);
	if (!mlx.first)
		return (vec_init(0,0,0));
	else if (mlx.first->type == SPHERE)
		normal = vec_normalize(vec_add_vec(t_point, mlx.first->pos, MINUS));
	return (normal);
}

t_hit	loop_objects(t_ray ray, t_vars mlx)
{
	t_hit	point;

	point.hit = 0;
	point.closest_pt.z = -1;
	point.point = -1;
	while (mlx.first)
	{
		if (mlx.first->type == SPHERE)
			point.point = hits_sphere(ray, mlx);
		if (point.point >= 0)
		{
			if (point.hit == 0 || point.point < point.closest_pt.z)
			{
				point.closest_pt.z = point.point;
				point.col = mlx.first->col;
				point.hit = 1;
				point.normal = get_normal(mlx, point, ray);
				//printf("%f\n", point.normal.x);
			}
		}
		mlx.first = mlx.first->next;
	}
	point.closest_pt = vec_add_vec(ray.origin, vec_mul(ray.direction, point.closest_pt.z), ADD);
	return (point);
}

t_color	check_meshes(t_ray ray, t_vars mlx, int idx)
{
	t_color col;
	t_hit	point;

	// if (idx > 5)
	// 	return (col_init(255, 255, 255));
	(void)idx;
	point = loop_objects(ray, mlx);
	col = col_mul(mlx.am_light->col, 0.8);
	if (point.hit)
	{
		t_pos	lumiere = vec_init(0.0,0.0,0);
		double	am_col = mlx.am_light->amlight->ratio;
		t_color	am = mlx.am_light->col;
		double intensite = ft_clamp(dot_product(vec_normalize(vec_add_vec(lumiere, point.closest_pt, MINUS)), point.normal), 0, 1) * 2500;
		intensite = intensite / (vec_length(vec_add_vec(lumiere, point.closest_pt, MINUS)) * vec_length(vec_add_vec(lumiere, point.closest_pt, MINUS)));
		//printf("%f\n", intensite);
		t_color lumcol = col_mul(col_init(0,0,255), intensite * 1);
		col.x = lumcol.x * point.col.x/255 + am.x * am_col;
		col.y = lumcol.y * point.col.y/255 + am.y * am_col;
		col.z = lumcol.z * point.col.z/255 + am.z * am_col;
		return(col);
	}
	return (col);
}

void	ray_color(t_ray ray, t_vars mlx, t_data *img, t_pos px)
{
	t_color		col;
	t_obj	*camera;
	int	i;

	i = 0;
	camera = mlx.camera;
	col = col_init(0,0,0);
	while (i < SAMPLES)
	{
		px.x = camera->camera->viewport->pixel_top_left.x + ((img->x + (myrand(px.x + i) - 0.5)) * camera->camera->viewport->pixel_delta.x);
		px.y = camera->camera->viewport->pixel_top_left.y + ((img->y + (myrand(px.y + i) - 0.5)) * camera->camera->viewport->pixel_delta.y);
		ray.direction = vec_normalize(vec_add_vec(px, mlx.camera->pos, MINUS)); //vecteur qui part de la camera vers le pixel voulu
		ray.origin = mlx.camera->pos;
		col = col_add_col(check_meshes(ray, mlx, 1), col);
		i++;
	}
	col.x = (int)ft_clamp((col.x/SAMPLES), 0, 255);
	col.y = (int)ft_clamp((col.y/SAMPLES), 0, 255);
	col.z = (int)ft_clamp((col.z/SAMPLES), 0, 255);
	i = create_trgb(0, col.x, col.y, col.z);
	my_mlx_pixel_put(img, img->y, img->x, i);
	return;
}

void	render_image(t_vars mlx, t_data *img)
{
	t_pos		pixel;
	t_obj		*camera;
	t_ray		ray;
	t_viewport	*vp;

	img->x = 0;
	img->y = 0;
	camera = camera_setup(mlx.first);
	mlx.camera = camera;
	mlx.am_light = get_amlight(mlx);
	vp = camera->camera->viewport;
	while (img->y < HEIGHT)
	{
		while (img->x < WIDTH)
		{
			pixel.x = vp->pixel_top_left.x + (img->x * vp->pixel_delta.x);
			pixel.y = vp->pixel_top_left.y + (img->y * vp->pixel_delta.y);
			pixel.z = vp->pixel_top_left.z;
			ray_color(ray, mlx, img, pixel);
			img->x = img->x + 1;
		}
		img->x = 0;
		img->y = img->y + 1;
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
	img.addr =  mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_image(mlx, &img);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
    mlx_hook(mlx.win, 17, 1L<<0, &close_window, &mlx);
	mlx_key_hook(mlx.win, &handle_key, &mlx);
	mlx_loop(mlx.mlx);
}
