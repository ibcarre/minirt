/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:30:26 by ibtihal           #+#    #+#             */
/*   Updated: 2025/09/16 15:43:12 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_pos	vec_div(t_pos vec, double nb)
{
	t_pos res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	if (nb == 0)
	{
		write(2, "Warning division by 0, res set to 0 0 0\n", 40);
		return (res);
	}
	res.x = vec.x / nb;
	res.y = vec.y / nb;
	res.z = vec.z / nb;
	return (res);
}

t_pos	vec_add(t_pos vec, double nb, int op)
{
	t_pos res;

	if (op == 1)
	{
		res.x = vec.x + nb;
		res.y = vec.y + nb;
		res.z = vec.z + nb;
	}
	else
	{
		res.x = vec.x - nb;
		res.y = vec.y - nb;
		res.z = vec.z - nb;
	}
	return (res);
}

t_pos	vec_mul(t_pos vec, double nb)
{
	t_pos res;

	res.x = vec.x * nb;
	res.y = vec.y * nb;
	res.z = vec.z * nb;
	return (res);
}

t_pos	vec_init(double x, double y, double z)
{
	t_pos	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

float	vec_length(t_pos vec)
{
	double	res;

	res = pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2);
	res = sqrt(res);
	return (res);
}

t_pos	vec_normalize(t_pos vec)
{
	return (vec_div(vec, vec_length(vec)));
}
