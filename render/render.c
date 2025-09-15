/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/09/15 16:58:59 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ray_color(t_ray ray, t_vars mlx, t_data *img)
{
	int		color;

	(void)mlx;
	(void)ray;
	color = create_trgb(0, 0, 0, 0);
	my_mlx_pixel_put(img, img->y, img->x, color);
	return;
}

void	render_image(t_vars mlx, t_data *img)
{
	double		view_h;
	double		view_w;
	t_pos		pixel_delta;
	t_pos		pixel_top_left;
	t_pos		pixel;
	t_obj		*camera;
	t_ray		ray;

	img->x = 0;
	img->y = 0;
	camera = get_camera(mlx.first);
	view_h = 15.0;
	view_w = view_h * (double)WIDTH/(double)HEIGHT;
	camera->camera->foc_length = FOC;
	camera->camera->viewport = vec_init(view_w, -view_h, -camera->camera->foc_length);
	pixel_delta.x = camera->camera->viewport.x/(double)WIDTH;
	pixel_delta.y = camera->camera->viewport.y/(double)HEIGHT;

	//top left pixel
	pixel_top_left.y = camera->pos.y - (camera->camera->viewport.y / 2) + (pixel_delta.y / 2);
	pixel_top_left.x = camera->pos.x - (camera->camera->viewport.x / 2) + (pixel_delta.x / 2);
	printf("FIRST PIXEL Y HEIGHT %f\n", pixel_top_left.y);
	printf("FIRST PIXEL X WIDTH %f\n", pixel_top_left.x);
	pixel_top_left.z = - (camera->camera->foc_length); // right handed orientation camera faces -z 
	while (img->y < HEIGHT)
	{
		while (img->x < WIDTH)
		{
			pixel.x = pixel_top_left.x + (img->x * pixel_delta.x);
			pixel.y = pixel_top_left.y + (img->y * pixel_delta.y);
			pixel.z = pixel_top_left.z;
			ray.direction = vec_add_vec(pixel, camera->pos, MINUS);
			ray.origin = camera->pos;
			ray_color(ray, mlx, img);
			img->x = img->x + 1;
		}
		img->x = 0;
		img->y = img->y + 1;
	}
	printf("LAST PIXEL Y %f\n", pixel.y);
	printf("LAST PIXEL X %f\n", pixel.x);
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
