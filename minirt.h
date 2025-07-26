/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:27:05 by ibtihal           #+#    #+#             */
/*   Updated: 2025/07/27 00:44:57 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 720
# define HEIGHT 480

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
}	t_vector3;

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
	int		ratio;
} t_amlight;

typedef struct s_camera
{
	t_vector3	orientation;
	int			fov;
} t_camera;

typedef struct s_light
{
	int			ratio;
} t_light;

typedef struct s_sphere
{
	int			diameter;
} t_sphere;

typedef struct s_plane
{
	t_vector3	normal;
} t_plane;

typedef struct s_cylinder
{
	int			diameter;
	int			height;
	t_vector3	normal;
} t_cylinder;

typedef struct s_obj
{
	t_type			type;
	t_vector3		pos;
	t_vector3		col;
	t_cylinder		*cylinder;
	t_plane			*plane;
	t_sphere		*sphere;
	t_light			*light;
	t_camera		*camera;
	t_amlight		*amlight;
	struct s_obj	*next;
}	t_obj;

void	print_obj_param(t_obj *object);
t_obj	*parsing(int fd);
void	free_objs(t_obj *first);
char	*skip_spaces(char *line);
char	*get_word(char *line);

#endif