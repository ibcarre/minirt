/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:37:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/03 16:43:42 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	col_init(int x, int y, int z)
{
	t_color	col;

	col.x = x;
	col.y = y;
	col.z = z;
	return (col);
}

t_color	col_add_col(t_color col, t_color color)
{
	t_color	res;

	res.x = col.x + color.x;
	res.y = col.y + color.y;
	res.z = col.z + color.z;
	return (res);
}

t_color	col_mul(t_color col, double x)
{
	t_color	res;

	res.x = col.x * x;
	res.y = col.y * x;
	res.z = col.z * x;
	return (res);
}

t_color	col_mul_col(t_color col, t_color col2)
{
	t_color	res;

	res.x = col.x * col2.x;
	res.y = col.y * col2.y;
	res.z = col.z * col2.z;
	return (res);
}
