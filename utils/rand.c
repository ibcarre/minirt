/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:47:23 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/03 16:41:13 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//https://vectrx.substack.com/p/lcg-xs-fast-gpu-rng

//LCG returns a number between (0 and 1)
double	myrand(int seed)
{
	unsigned int	result;

	seed = seed * 747796405 + 2891336453;
	result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
	return (((double)result / (double)UINT_MAX));
}

//returns a number between min and max
double	rand_min_max(int seed, int min, int max)
{
	return (min + (max - min) * myrand(seed));
}

t_pos	random_vec(int seed)
{
	t_pos	vec;

	vec.x = myrand(seed);
	vec.y = myrand(seed * 2 + 7);
	vec.z = myrand(seed * 3 + 13);
	return (vec);
}

t_pos	random_vec_min_max(int seed, int min, int max)
{
	t_pos	vec;

	vec.x = rand_min_max(seed * 2 + 7, min, max);
	vec.y = rand_min_max(seed * 3 + 13, min, max);
	vec.z = rand_min_max(seed, min, max);
	return (vec);
}
