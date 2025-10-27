/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:27:05 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/27 12:39:17 by ibtihal          ###   ########.fr       */
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
# define INTENSITE 150

# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "../utils/get_next_line.h"

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
} t_amlight;

typedef struct	s_viewport {
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
} t_camera;

typedef struct s_light
{
	double		ratio;
} t_light;

typedef struct s_sphere
{
	double		rayon;
	int			backface;
} t_sphere;

typedef struct s_plane
{
	t_pos	normal;
} t_plane;

typedef struct s_cylinder
{
	double		diameter;
	double		height;
	t_pos		normal;
} t_cylinder;

typedef	struct	s_ray
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
	t_camera		*camera; //pas de next => pas 2 cameras dans une scène
	t_amlight		*amlight; //pas de next amlight non plus
	struct s_obj	*next;
}	t_obj;

typedef struct	s_hit
{
	double	point;
	t_pos	closest_pt;
	int		hit;
	t_color	col;
	t_pos	normal;
	double	delta;
	int		type;
}	t_hit;

// typedef struct s_obj
// {
// 	t_cylinder		*cylinder; //setup as NULL si ils existent pas !!!important!!!!
// 	t_plane			*plane;
// 	t_sphere		*sphere;
// 	t_light			*light;
// 	t_camera		*camera;
// 	t_amlight		*amlight;
// }	t_obj;
// typedef struct s_cylinder
// {
// 	t_pos			pos;
// 	t_color			col;
// 	double		diameter;
// 	double		height;
// 	t_pos		normal;
// 	struct s_cylinder	*next;
// } t_cylinder;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		x;
	int		y;
	int		endian;
}	t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_obj	*first;
	t_obj	*camera;
	t_obj	*am_light;
}	t_vars;

void	print_obj_param(t_obj *object);
t_obj	*parsing(int fd);
void	free_objs(t_obj *first);
char	*skip_spaces(char *line);
t_obj	*get_last(t_obj *first);
void	fill_obj(char *line, t_obj **last);
double	ft_atof(char **str, int *works);
int		ft_atoi(char **str);
int		is_digit(char c);
int		fill_col(t_obj *obj, char **line);
int		fill_pos(t_obj *obj, char **line);
int		fill_or(t_pos *pos, char **line);
double	ft_clamp(double nb, double min, double max);
void	render(t_obj *first);
t_pos	vec_div(t_pos vec, double nb);
t_pos	vec_add(t_pos vec, double nb, int op);
t_pos	vec_mul(t_pos vec, double nb);
t_pos	vec_init(double x, double y, double z);
t_pos	vec_div_vec(t_pos vec, t_pos vec2);
t_pos	vec_add_vec(t_pos vec, t_pos vec2, int nb);
t_pos	vec_mul_vec(t_pos vec, t_pos vec2);
double	vec_length(t_pos vec);
t_pos	vec_normalize(t_pos vec);
double	dot_product(t_pos vec, t_pos vec2);
t_obj	*camera_setup(t_obj *camera);
double	rand_min_max(int seed, int min, int max);
double myrand(int seed);
t_color	col_init(int x, int y, int z);
t_color	col_add_col(t_color col, t_color color);
double	vec_length_squared(t_pos vec);
t_pos	random_unit_vec_dir(int	seed, t_pos dir);
t_color col_mul(t_color col, double x);
void	print_vec(char *s, t_pos vec);
t_obj	*get_amlight(t_vars mlx);
double	abs_f(double x);
t_color col_mul_col(t_color col, t_color col2);
void	loading(int	i);
t_pos	cross(t_pos x, t_pos y);

#endif

//setup sphere->next => sphere 
// camera et ambient lighting dans OBJ