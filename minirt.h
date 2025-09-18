/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:27:05 by ibtihal           #+#    #+#             */
/*   Updated: 2025/09/18 21:38:03 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 720
# define HEIGHT 480
# define FOC 1.0
# define INT_MAX 0x7fffffff
# define MINUS 0
# define ADD 1

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "./utils/get_next_line.h"

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

typedef struct s_camera
{
	t_pos		orientation;
	int			fov;
	double		foc_length;
	t_pos		viewport;
} t_camera;

typedef struct s_light
{
	double		ratio;
} t_light;

typedef struct s_sphere
{
	double		diameter;
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

typedef	struct	s_viewport
{
	t_pos	view_u;
	t_pos	view_v;
}	t_viewport;

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
	t_camera		*camera;
	t_amlight		*amlight;
	struct s_obj	*next;
}	t_obj;

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
float	vec_length(t_pos vec);
t_pos	vec_normalize(t_pos vec);
double	dot_product(t_pos vec, t_pos vec2);

#endif