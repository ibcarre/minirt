/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:14:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 19:10:00 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sp 0,-50.5,-100 100 10,0,255

#include "../includes/minirt.h"

void	get_y(t_global *glob, t_pos *xy)
{
	pthread_mutex_lock(&(glob->mutex));
	glob->img->y = glob->img->y + 1;
	xy->y = glob->img->y;
	pthread_mutex_unlock(&(glob->mutex));
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
			pixel = vec_add_vec(global->vp->pixel_top_left,
					vec_mul(global->vp->pixel_delta_u, xy.x), ADD);
			pixel = vec_add_vec(pixel,
					vec_mul(global->vp->pixel_delta_v, xy.y), ADD);
			ray_color(ray, pixel, xy, global);
			xy.x = xy.x + 1;
		}
		get_y(global, &xy);
		loading(xy.y);
	}
	return (NULL);
}

void	render_image(t_vars mlx, t_data *img)
{
	pthread_t	threads[CORES];
	t_global	glob;
	int			i;

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
	t_vars	mlx;
	t_data	img;

	mlx.first = first ;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "blender");
	img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img,
			&img.bits_per_pixel, &img.line_length, &img.endian);
	render_image(mlx, &img);
	printf("\n");
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 17, 1L << 0, &close_window, &mlx);
	mlx_key_hook(mlx.win, &handle_key, &mlx);
	mlx_loop(mlx.mlx);
}
