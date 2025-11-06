/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:18:00 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 19:01:16 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_pos	col_mul2(t_color col, double x)
{
	t_pos	res;

	res.x = col.x * x;
	res.y = col.y * x;
	res.z = col.z * x;
	return (res);
}

t_pos	col_mul_vec(t_color col, t_pos vec)
{
	t_pos	res;

	res.x = col.x * vec.x;
	res.y = col.y * vec.y;
	res.z = col.z * vec.z;
	return (res);
}

t_color	col_div(t_pos col, double x)
{
	t_color	res;

	res.x = col.x / x;
	res.y = col.y / x;
	res.z = col.z / x;
	return (res);
}
