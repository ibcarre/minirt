/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:35 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 15:43:13 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_obj	*fill_alight(char *line, t_obj **obj)
{
	int		i;
	int		works;
	double	ratio;

	i = 0;
	works = 1;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	(*obj)->amlight = malloc(sizeof(t_amlight));
	if (!((*obj)->amlight))
		return (free(*obj), *obj = NULL);
	ratio = ft_clamp(ft_atof(&line, &works), 0, 1);
	(*obj)->amlight->ratio = ratio;
	if (!fill_col(*obj, &line) || !works)
	{
		free_objs(*obj);
		(*obj) = NULL;
		return (NULL);
	}
	return (*obj);
}

t_obj	*fill_sphere(char *line, t_obj **obj)
{
	int	works;
	int	i;

	i = 0;
	works = 1;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	if (!fill_pos(*obj, &line))
		return (free(*obj), (*obj) = NULL);
	(*obj)->sphere = malloc(sizeof(t_sphere));
	if (!((*obj)->sphere))
		return (free((*obj)->sphere), free(*obj), *obj = NULL);
	(*obj)->sphere->rayon = (ft_atof(&line, &works)) / 2;
	if ((*obj)->sphere->rayon < 0)
	{
		write(2, "NEG DIAMETER\n", 13);
		works = 0;
	}
	if (works)
		works = fill_col(*obj, &line);
	if (!works)
		return (free_objs(*obj), *obj = NULL);
	return (*obj);
}

t_obj	*fill_light(char *line, t_obj **obj)
{
	int		i;
	int		works;
	double	ratio;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	works = fill_pos(*obj, &line);
	(*obj)->light = malloc(sizeof(t_light));
	if (!((*obj)->light))
		works = 0;
	if (!works)
		return (free(*obj), *obj = NULL);
	ratio = ft_clamp(ft_atof(&line, &works), 0, 1);
	(*obj)->light->ratio = ratio;
	if (!fill_col(*obj, &line) || !works)
	{
		free_objs(*obj);
		(*obj) = NULL;
		return (NULL);
	}
	return (*obj);
}

t_obj	*fill_camera(char *line, t_obj **obj)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	i = 1;
	(*obj)->camera = malloc(sizeof(t_camera));
	(*obj)->camera->viewport = NULL;
	if (!fill_pos(*obj, &line) || !((*obj)->camera))
		return (free(*obj), *obj = NULL);
	if (!fill_or(&((*obj)->camera->orientation), &line))
		return (free_objs(*obj), *obj = NULL);
	(*obj)->camera->fov = ft_clamp(ft_atof(&line, &i), 0, 180);
	if (!i)
		return (free_objs(*obj), *obj = NULL);
	(*obj)->camera->viewport = malloc(sizeof(t_viewport));
	if (!((*obj)->camera->viewport))
		return (free_objs(*obj), *obj = NULL);
	return (*obj);
}

t_obj	*fill_plane(char *line, t_obj **obj)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	(*obj)->plane = malloc(sizeof(t_plane));
	if (!fill_pos(*obj, &line) || !((*obj)->plane))
		return (free(*obj), *obj = NULL);
	if (!fill_or(&((*obj)->plane->normal), &line))
		return (free_objs(*obj), *obj = NULL);
	if (!fill_col(*obj, &line))
	{
		free_objs(*obj);
		(*obj) = NULL;
	}
	return (*obj);
}
