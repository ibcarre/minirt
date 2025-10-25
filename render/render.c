/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/25 21:43:27 by ibtihal          ###   ########.fr       */
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

double	hits_sphere(t_ray ray, t_obj *first)
{
	t_pos	or_to_oc; //rayon to centre
	double	a;
	double	h;
	double	c;
	double delta;

	or_to_oc = vec_add_vec(first->pos, ray.origin, MINUS);
	a = vec_length(ray.direction) * vec_length(ray.direction);//dot_product(ray.direction, ray.direction);
	h =  dot_product(ray.direction, or_to_oc); //-2 * dot_product(ray.direction, or_to_oc);
	c = my_sq(vec_length(or_to_oc)) - my_sq(first->sphere->rayon);//dot_product(cr, cr) - mlx.first->sphere->rayon * mlx.first->sphere->rayon;
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

t_pos	get_normal(t_obj *first, t_hit *point, t_ray ray)
{
	t_pos	normal;
	t_pos	t_point;

	t_point = vec_add_vec(ray.origin, vec_mul(ray.direction, point->closest_pt.z), ADD);
	if (!first)
		return (vec_init(0,0,0));
	else if (first->type == SPHERE)
		normal = vec_normalize(vec_add_vec(t_point, first->pos, MINUS));
	else if (first->type == PLANE)
	{
		if (dot_product(ray.direction, first->plane->normal) > 0)
			normal = vec_init(-first->plane->normal.x, -first->plane->normal.y, -first->plane->normal.z);
		else
			normal = first->plane->normal;
	}
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
		t = dot_product(point, first->plane->normal)/denom;
		if (t > 1e-6)
			return (t);
		return (-1);
	}
	return (-1);
}

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


t_hit	check_shadow(t_ray ray, t_obj *first, t_hit *point, double	length)
{
	double	length_hit;
	point->hit = 0;
	point->closest_pt.z = -1;
	point->point = -1;

	while (first)
	{
		point->type = first->type; 
		if (first->type == SPHERE)
			point->point = hits_sphere(ray, first);
		else if (first->type == PLANE)
			point->point = hits_plane(ray, first);
		if (point->point >= 0)
		{
			//printf("LENGTH HIT LIGHT %f\n", length);
			point->closest_pt = vec_add_vec(ray.origin, vec_mul(ray.direction, point->point), ADD);
			length_hit = vec_length_squared(vec_add_vec(point->closest_pt, ray.origin, MINUS));
			get_normal(first, point, ray);
			//printf("LENGTH OBJ 0BJ %f\n", length_hit);
			//printf("ray origin %f %f %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
			//printf("point %f %f %f\n", point->closest_pt.x, point->closest_pt.y, point->closest_pt.z);
			if (dot_product(vec_normalize(vec_add_vec(point->closest_pt, ray.origin, MINUS)), point->normal) > 0 || first->type != PLANE)
			{
				// printf("%f\n", dot_product(vec_add_vec(point->closest_pt, ray.origin, MINUS), vec_add_vec(point->normal, ray.origin, MINUS)));
				if (length_hit < length)
					return (point->hit = 1, *point);
			}
			point->point = -1;
		}
		first = first->next;
	}
	return (*point);
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
				//return col_init(255,255,255);
				intensite = ft_clamp(dot_product(vec_normalize(vec_add_vec(mlx.first->pos, point.closest_pt, MINUS)), point.normal), 0, 1) * INTENSITE;
				intensite = intensite / vec_length_squared(vec_add_vec(mlx.first->pos, point.closest_pt, MINUS));
				//printf("\n%f\n", intensite);
				// lumcol = col_mul(mlx.first->col, mlx.first->light->ratio * intensite);
				// lumcol = col_mul_col(lumcol, point.col);
				// col = col_add_col(lumcol, col);
				lumcol.x = mlx.first->col.x * mlx.first->light->ratio * intensite * point.col.x;
				lumcol.y = mlx.first->col.y * mlx.first->light->ratio * intensite * point.col.y;
				lumcol.z = mlx.first->col.z * mlx.first->light->ratio * intensite * point.col.z;
				col = vec_add_vec(lumcol, col, ADD);
			}
		}
		mlx.first = mlx.first->next;
	}
	//return col_init(0,0,0);
	// lumcol = col_mul(mlx.am_light->col, mlx.am_light->amlight->ratio);
	// col = col_add_col(col, lumcol);
	// col = col_mul_col(col, point.col);
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
	// t_hit	shadow;
	t_color	lumcol;
	// double	intensite;

	// if (idx > 5)
	// 	return (col_init(255, 255, 255));
	loop_objects(ray, mlx.first, &point);
	col = col_mul(mlx.am_light->col, 0.8);
	if (point.hit)
	{
		//return(point.col);
		//printf("%f %f %f\n", point.closest_pt.x, point.closest_pt.y, point.closest_pt.z);
		//t_pos	lumiere = vec_init(0.0,0,15);
		// double	am_col = mlx.am_light->amlight->ratio;
		// t_color	am = mlx.am_light->col;
		// ray.direction = vec_normalize(vec_add_vec(lumiere, point.closest_pt, MINUS));
		// check_shadow(ray, mlx.first, &shadow, vec_length_squared(vec_add_vec(ray.direction, ray.origin, MINUS)));
		// intensite = ft_clamp(dot_product(vec_normalize(vec_add_vec(lumiere, point.closest_pt, MINUS)), point.normal), 0, 1) * 10000;
		// intensite = intensite / vec_length_squared(vec_add_vec(lumiere, point.closest_pt, MINUS));
		//jadditionne ttes les couleurs obtenues puis je les divise par le nombre de light
		//printf("%f\n", intensite);
		//return(col_init(255,255,255));
		//printf("%f\n", intensite);
		// printf("POINT NORMAL OBJ HIT CAMERA %f %f %f\n", point.normal.x, point.normal.y, point.normal.z);
		// printf("TYPE %i\n", point.type);
		ray.origin = vec_add_vec(point.closest_pt, vec_mul(point.normal, 0.001), ADD);
		lumcol = check_lights(ray, mlx, point); //col_mul(col_init(0,0,255), intensite * 0.5);
		// if (shadow.hit)
		// {
		// 	col.x = ((lumcol.x + point.col.x)/2 + am.x * am_col) * 0.7;
		// 	col.y = ((lumcol.y + point.col.y)/2 + am.y * am_col) * 0.7;
		// 	col.z = ((lumcol.z + point.col.z)/2 + am.z * am_col) * 0.7;
		// 	return(col);
		// }
		// col.x = (lumcol.x + point.col.x)/2 + am.x * am_col;
		// col.y = (lumcol.y + point.col.y)/2 + am.y * am_col;
		// col.z = (lumcol.z + point.col.z)/2 + am.z * am_col;
		// col.x = (point.col.x + am.x * am_col) * intensite;
		// col.y = (point.col.y + am.y * am_col) * intensite;
		// col.z = (point.col.z + am.z * am_col) * intensite;
		return(lumcol);
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
		col = col_add_col(check_meshes(ray, mlx), col);
		i++;
	}
	col.x = (int)ft_clamp((col.x/SAMPLES), 0, 255);
	col.y = (int)ft_clamp((col.y/SAMPLES), 0, 255);
	col.z = (int)ft_clamp((col.z/SAMPLES), 0, 255);
	i = create_trgb(0, col.x, col.y, col.z);
	my_mlx_pixel_put(img, img->y, img->x, i);
	return;
}

// t_vars	fix_planes_norm(t_vars *mlx)
// {
// 	t_pos	norm;
// 	t_obj	*first;
	
// 	first = mlx->first;
// 	while (mlx->first)
// 	{
// 		if (mlx->first->type == PLANE)
// 		{
// 			if (dot_product(mlx->first->plane->normal, mlx->camera->camera->orientation) < 0)
// 			{
// 				printf("QSDQSDQSD\n");
// 				norm = vec_init(-mlx->first->plane->normal.x, -mlx->first->plane->normal.y, -mlx->first->plane->normal.z);
// 				mlx->first->plane->normal.x = norm.x;
// 				mlx->first->plane->normal.y = norm.y;
// 				mlx->first->plane->normal.z = norm.z;
// 			}
// 		}
// 		mlx->first = mlx->first->next;
// 	}
// 	mlx->first = first;
// 	return (*mlx);
// }

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
		loading(img->y);
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
	write(1, "\rRENDERING 100%", 15);
	printf("\n");
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
    mlx_hook(mlx.win, 17, 1L<<0, &close_window, &mlx);
	mlx_key_hook(mlx.win, &handle_key, &mlx);
	mlx_loop(mlx.mlx);
}
