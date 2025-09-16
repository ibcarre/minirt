/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_on_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:26 by ibtihal           #+#    #+#             */
/*   Updated: 2025/09/16 15:37:21 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_pos	vec_div_vec(t_pos vec, t_pos vec2)
{
	t_pos res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	if (vec2.x == 0 || vec2.y == 0 || vec2.z == 0)
	{
		write(2, "Warning division by 0, res set to 0 0 0\n", 40);
		return (res);
	}
	res.x = vec.x / vec2.x;
	res.y = vec.y / vec2.y;
	res.z = vec.z / vec2.z;
	return (res);
}

t_pos	vec_add_vec(t_pos vec, t_pos vec2, int nb)
{
	t_pos res;

	if (nb == 1)
	{
		res.x = vec.x + vec2.x;
		res.y = vec.y + vec2.y;
		res.z = vec.z + vec2.z;
	}
	else
	{
		res.x = vec.x - vec2.x;
		res.y = vec.y - vec2.y;
		res.z = vec.z - vec2.z;
	}
	return (res);
}

t_pos	vec_mul_vec(t_pos vec, t_pos vec2)
{
	t_pos res;

	res.x = vec.x * vec2.x;
	res.y = vec.y * vec2.y;
	res.z = vec.z * vec2.z;
	return (res);
}
