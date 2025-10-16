/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/15 17:40:13 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

double	hits_sphere(t_ray ray, t_vars mlx, t_pos *center)
{
	t_pos	or_to_oc; //rayon to centre
	double	a;
	double	h;
	double	c;
	double delta;

	while (mlx.first)
	{
		if (mlx.first->type == SPHERE)
		{
			*center = mlx.first->pos;
			or_to_oc = vec_add_vec(mlx.first->pos, ray.origin, MINUS);
			a = vec_length(ray.direction) * vec_length(ray.direction);//dot_product(ray.direction, ray.direction);
			h =  dot_product(ray.direction, or_to_oc); //-2 * dot_product(ray.direction, or_to_oc);
			c = my_sq(vec_length(or_to_oc)) - my_sq(mlx.first->sphere->rayon);//dot_product(cr, cr) - mlx.first->sphere->rayon * mlx.first->sphere->rayon;
			delta = sqrt(my_sq(h) - a * c);
			if (delta >= 0)
				return ((h - sqrt(delta))/(a)); // moins pour obtenir la solution la plus proche de la caméra, return negatif quand on est dans la sphère (forcément...)
			else
				return (-1);
		}
		mlx.first = mlx.first->next;
	}
	return (-1);
}

t_color	check_meshes(t_ray ray, t_vars mlx)
{
	t_pos	norm_v;
	t_color col;
	double	t;
	t_pos	inter_norm;
	t_pos	sphere_c;
	//double	vec_sens;

	sphere_c = vec_init(0, 0, 0); //center_sphere
	t = hits_sphere(ray, mlx, &sphere_c);
	//plus le t est petit plus il est proche y = at + b / / a => ray.dir, b => ray.origin
	if (t >= 0) //pour pas obtenir les solutions derrière la caméra
	{										//vec_mul ray_dir a la solution pour laquelle ray_dir touche sphere
		inter_norm = vec_add_vec(ray.origin, vec_mul(ray.direction, t), ADD); //vecteur origin rayon to point d'intersection rayon sphere
		inter_norm = vec_add_vec(inter_norm, sphere_c, MINUS);
		//inter_norm = vec_add_vec(sphere_c, inter_norm, ADD);
		inter_norm = vec_normalize(inter_norm);
		//vec_sens = dot_product(inter_norm, ray.direction);
		//printf("SENS DU VECTEUR %f\n", vec_sens); //negatif quand pas meme sens et positif quand meme sens
		// donc negatif front face et positif backface => normal always points out
		col.x = (int)((inter_norm.x + 1.0) * 127.5);
		col.y = (int)((inter_norm.y + 1.0) * 127.5);
		col.z = (int)((inter_norm.z + 1.0) * 127.5);
	}
	else {
		norm_v = vec_normalize(ray.direction);
		float a = 0.5 * (norm_v.y + 1);
		col.x = (((1 - a) + (a * 0.5)) * 255);
		col.y = (((1 - a) + (a * 0.7)) * 255);
		col.z = (((1 - a) + (a * 1)) * 255);
	}
	return (col);

}

void	ray_color(t_ray ray, t_vars mlx, t_data *img, t_pos px)
{
	t_color		col;
	int	i;
	t_obj	*camera;

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
	col.x = (int)ft_clamp(col.x/SAMPLES, 0, 255);
	col.y = (int)ft_clamp(col.y/SAMPLES, 0, 255);
	col.z = (int)ft_clamp(col.z/SAMPLES, 0, 255);
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
