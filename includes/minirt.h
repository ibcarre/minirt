/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:27:05 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/20 20:58:32 by ibaaziz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 720
# define HEIGHT 480
# define MINUS 0
# define ADD 1
# define SAMPLES 5
# define M_PI 3.14159265358979323846
# define INTENSITE 100
# define CORES 20

# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "../utils/get_next_line.h"
# include <pthread.h>

typedef struct s_color
{
	int	x;
	int	y;
	int	z;
}	t_color;

typedef struct s_pos
{
	double	x;
	double	y;
	double	z;
}	t_pos;

typedef enum e_type
{
	A_LIGHT,
	LIGHT,
	SPHERE,
	PLANE,
	CAMERA,
	CYLINDER
}	t_type;

typedef struct s_amlight
{
	double		ratio;
}	t_amlight;

typedef struct s_viewport
{
	double		view_h;
	double		view_w;
	t_pos		pixel_delta_u;
	t_pos		pixel_delta_v;
	t_pos		vport_u;
	t_pos		vport_v;
	t_pos		pixel_top_left;
}	t_viewport;

typedef struct s_camera
{
	t_pos			orientation;
	int				fov;
	t_viewport		*viewport;
}	t_camera;

typedef struct s_light
{
	double		ratio;
}	t_light;

typedef struct s_sphere
{
	double		rayon;
	int			backface;
}	t_sphere;

typedef struct s_plane
{
	t_pos	normal;
}	t_plane;

typedef struct s_cylinder
{
	double		rayon;
	double		height;
	t_pos		normal;
}	t_cylinder;

typedef struct s_ray
{
	t_pos	origin;
	t_pos	direction;
}	t_ray;

typedef struct s_obj
{
	t_type			type;
	t_pos			pos;
	t_color			col;
	t_cylinder		*cylinder;
	t_plane			*plane;
	t_sphere		*sphere;
	t_light			*light;
	t_camera		*camera;
	t_amlight		*amlight;
	struct s_obj	*next;
}	t_obj;

typedef struct s_cylhit
{
	double	t;
	int		endcap;
}	t_cylhit;

typedef struct s_hit
{
	double		point;
	t_pos		closest_pt;
	int			hit;
	t_color		col;
	t_pos		normal;
	double		delta;
	int			type;
	t_cylhit	cyl_point;
}	t_hit;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		y;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_obj	*first;
	t_obj	*camera;
	t_obj	*am_light;
}	t_vars;

typedef struct s_global
{
	t_vars			mlx;
	t_data			*img;
	t_viewport		*vp;
	pthread_mutex_t	mutex;
}	t_global;

typedef struct s_axis
{
	t_pos	u;
	t_pos	v;
	t_pos	w;
}	t_axis;

typedef struct s_shading
{
	double	intensity;
	t_pos	lumcol;
	t_pos	col;
}	t_shading;

typedef struct s_cyl
{
	t_pos		center;
	t_pos		axe;
	t_pos		top;
	t_pos		bot;
	t_pos		rdxaxe;
	double		r2;
	double		ra;
	double		aa;
	t_pos		b0;
	double		b;
	double		d;
	double		delta;
	double		t;
	t_cylhit	p;
}	t_cyl;

t_obj		*parsing(int fd);
void		free_objs(t_obj *first);
char		*skip_spaces(char *line);
t_obj		*get_last(t_obj *first);
void		fill_obj(char *line, t_obj **last);
double		ft_atof(char **str, int *works);
int			ft_atoi(char **str, int *works);
int			is_digit(char c);
int			fill_col(t_obj *obj, char **line);
int			fill_pos(t_obj *obj, char **line);
int			fill_or(t_pos *pos, char **line);
double		ft_clamp(double nb, double min, double max);
int			render(t_obj *first);
t_pos		vec_div(t_pos vec, double nb);
t_pos		vec_add(t_pos vec, double nb, int op);
t_pos		vec_mul(t_pos vec, double nb);
t_pos		vec_init(double x, double y, double z);
t_pos		vec_div_vec(t_pos vec, t_pos vec2);
t_pos		vec_add_vec(t_pos vec, t_pos vec2, int nb);
t_pos		vec_mul_vec(t_pos vec, t_pos vec2);
double		vec_length(t_pos vec);
t_pos		vec_normalize(t_pos vec);
double		dot_product(t_pos vec, t_pos vec2);
t_obj		*camera_setup(t_obj *camera);
double		rand_min_max(int seed, int min, int max);
double		myrand(int seed);
t_color		col_init(int x, int y, int z);
t_color		col_add_col(t_color col, t_color color);
double		vec_length_squared(t_pos vec);
t_color		col_mul(t_color col, double x);
void		print_vec(char *s, t_pos vec);
t_obj		*get_amlight(t_vars mlx);
double		abs_f(double x);
t_color		col_mul_col(t_color col, t_color col2);
void		loading(int i);
t_pos		cross(t_pos x, t_pos y);
int			is_rt_file(char *filename);
int			is_digit(char c);
void		get_sign(int *sign, char *str, int *i, long *test);
double		hits_sphere(t_ray ray, t_obj *first);
t_pos		get_normal(t_obj *first, t_hit *point, t_ray ray);
double		hits_plane(t_ray ray, t_obj *first);
void		my_mlx_pixel_put(t_data *data, int height, int width, int color);
int			close_window(t_vars *mlx);
int			handle_key(int keycode, t_vars *mlx);
double		my_sq(double x);
int			create_trgb(int t, int r, int g, int b);
t_cylhit	hits_cylinder(t_ray ray, t_obj *obj);
t_obj		*fill_plane(char *line, t_obj **obj);
t_obj		*fill_camera(char *line, t_obj **obj);
t_obj		*fill_light(char *line, t_obj **obj);
t_obj		*fill_sphere(char *line, t_obj **obj);
t_obj		*fill_alight(char *line, t_obj **obj);
t_pos		col_mul2(t_color col, double x);
t_pos		col_mul_vec(t_color col, t_pos vec);
t_color		col_div(t_pos col, double x);
void		ray_color(t_pos px, t_pos xy, t_global *global);
void		shading(t_shading *shader, t_vars mlx, t_hit point);
t_color		check_lights(t_ray ray, t_vars mlx, t_hit point);
t_color		check_meshes(t_ray ray, t_vars mlx);
void		show_img(t_color col, t_global *global, t_pos xy);
t_hit		loop_objects(t_ray ray, t_obj *first, t_hit *point);
t_hit		check_shadow(t_ray ray, t_obj *first, t_hit *shadow, double length);

#endif
