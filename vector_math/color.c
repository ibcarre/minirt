/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:37:36 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/15 17:41:10 by ibtihal          ###   ########.fr       */
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