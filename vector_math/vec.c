/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:26 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/03 16:45:14 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	vec_length_squared(t_pos vec)
{
	double	res;

	res = pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
	return (res);
}

t_pos	vec_normalize(t_pos vec)
{
	return (vec_div(vec, vec_length(vec)));
}

double	dot_product(t_pos vec, t_pos vec2)
{
	return (vec.x * vec2.x + vec.y * vec2.y + vec.z * vec2.z);
}

t_pos	cross(t_pos x, t_pos y)
{
	t_pos	res;

	res.x = x.y * y.z - x.z * y.y;
	res.y = x.z * y.x - x.x * y.z;
	res.z = x.x * y.y - x.y * y.x;
	return (res);
}
