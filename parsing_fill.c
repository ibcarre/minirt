/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:35 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/21 18:17:38 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_ceil(double *ratio)
{
	printf("WAR : RATIO VALUE TOO LOW/HIGH IS NOW DEFAULT VALUE\n");
	if (*ratio < 0)
		*ratio = 0;
	else
		*ratio = 1;
}

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
	ratio = ft_atof(&line, &works);
	if(ratio < 0 || ratio > 1)
		ft_ceil(&ratio);
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
		return(free(*obj), (*obj) = NULL);
	(*obj)->sphere = malloc(sizeof(t_sphere));
	if (!((*obj)->sphere))
		return (free((*obj)->sphere), free(*obj), *obj = NULL);
	(*obj)->sphere->diameter = ft_atof(&line, &works);
	if ((*obj)->sphere->diameter < 0)
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
	ratio = ft_atof(&line, &works);
	if(ratio < 0 || ratio > 1)
		ft_ceil(&ratio);
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
	line[0] = 'q';
	return (*obj);
}


void	fill_obj(char *line, t_obj **last)
{
	if (!*last)
		return ;
	if ((*last)->type == A_LIGHT)
		fill_alight(line, last);
	else if ((*last)->type == SPHERE)
		fill_sphere(line, last);
	else if ((*last)->type == LIGHT)
		fill_light(line, last);
	else if ((*last)->type == CAMERA)
		fill_camera(line, last);
	/*else if (last ->type == PLANE)
		fill_camera(line, last);
	else if (last ->type == CYLINDER)
		fill_cylinder(line, last);*/
	return ;
}
