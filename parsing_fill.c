/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:35 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/14 19:37:16 by ibtihal          ###   ########.fr       */
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

	works = fill_pos(*obj, &line);
	(*obj)->sphere = malloc(sizeof(t_sphere));
	works ++;
	return (*obj);
}

/*
t_obj	*fill_sphere(char *line, t_obj **obj)
{
	int		i;
	double	ratio;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	(*obj)->sphere = malloc(sizeof(t_sphere));
	if (!((*obj)->sphere))
	{
		free(*obj);
		*obj = NULL;
		return (NULL);
	}
	if (!fill_pos(obj, &line[i]))
	{
		free_objs(*obj);
		(*obj) = NULL;
		return (NULL);
	}
	while (is_digit(line[i]))
		i++;
	//if (!fill_col(&obj, &line[i], &i) || fill_pos(&obj, &line[i]))
	if (!fill_col(obj, &line[i], &i))
	{

	}
	return (*obj);
}*/

void	fill_obj(char *line, t_obj **last)
{
	if (!*last)
		return ;
	if ((*last)->type == A_LIGHT)
		fill_alight(line, last);
	//else if ((*last)->type == SPHERE)
	//	fill_sphere(line, *last);
	/*else if (last ->type == LIGHT)
		fill_light(line, last);
	else if (last ->type == CAMERA)
		fill_camera(line, last);
	else if (last ->type == PLANE)
		fill_camera(line, last);
	else if (last ->type == CYLINDER)
		fill_cylinder(line, last);*/
	return ;
}
