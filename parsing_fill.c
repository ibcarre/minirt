/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:09:35 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/12 21:35:18 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fill_col(t_obj **obj, char *line, int *d)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	line = skip_spaces(line);
	while(line[i] && !ft_isspace(line[i]))
	{
		if (line[i] == ',')
			commas ++;
		i++;
	}
	if (commas != 2)
		return (0);
	(*obj)->col.x = ft_atoi(line);
	i = 0;
	while (line[i - 1] != ',')
		i++;
	(*obj)->col.y = ft_atoi(line);
	while (line[i - 1] != ',')
		i++;
	(*obj)->col.z = ft_atoi(line);
	*d = *d + i;
	return (1);
}

int	fill_pos(t_obj **obj, char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	line = skip_spaces(line);
	while(line[i] && !ft_isspace(line[i]))
	{
		if (line[i] == ',')
			commas ++;
		i++;
	}
	if (commas != 2)
		return (0);
	(*obj)->pos.x = ft_atoi(line);
	i = 0;
	while (line[i - 1] != ',')
		i++;
	(*obj)->pos.y = ft_atoi(line);
	while (line[i - 1] != ',')
		i++;
	(*obj)->pos.z = ft_atoi(line);
	return (1);
}

t_obj	*fill_alight(char *line, t_obj **obj)
{
	int		i;
	double	ratio;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	(*obj)->amlight = malloc(sizeof(t_amlight));
	ratio = ft_atof(line, (void **)&((*obj)->amlight), &i);
	if (!((*obj)->amlight))
	{
		free(*obj);
		*obj = NULL;
		return (NULL);
	}
	(*obj)->amlight->ratio = ratio;
	while (is_digit(line[i]))
		i++;
	//if (!fill_col(&obj, &line[i], &i) || fill_pos(&obj, &line[i]))
	if (!fill_col(obj, &line[i], &i))
	{
		free_objs(*obj);
		(*obj) = NULL;
		return (NULL);
	}
	return (*obj);
}

t_obj	*fill_sphere(char *line, t_obj **obj)
{
	int		i;
	double	ratio;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	line = skip_spaces(&line[i]);
	(*obj)->amlight = malloc(sizeof(t_amlight));
	ratio = ft_atof(line, (void **)&((*obj)->amlight), &i);
	if (!((*obj)->amlight))
	{
		free(*obj);
		*obj = NULL;
		return (NULL);
	}
	(*obj)->amlight->ratio = ratio;
	while (is_digit(line[i]))
		i++;
	//if (!fill_col(&obj, &line[i], &i) || fill_pos(&obj, &line[i]))
	if (!fill_col(obj, &line[i], &i))
	{
		free_objs(*obj);
		(*obj) = NULL;
		return (NULL);
	}
	return (*obj);
}

void	fill_obj(char *line, t_obj **last)
{
	if (!*last)
		return ;
	if ((*last)->type == A_LIGHT)
		*last = fill_alight(line, last);
	else if ((*last)->type == SPHERE)
		fill_sphere(line, *last);
	/*else if (last ->type == LIGHT)
		fill_light(line, last);
	/*else if (last ->type == CAMERA)
		fill_camera(line, last);
	/*else if (last ->type == PLANE)
		fill_camera(line, last);
	/*else if (last ->type == CYLINDER)
		fill_cylinder(line, last);*/
	if (!last)
		write(2, "Parsing failed\n", 15);
}
