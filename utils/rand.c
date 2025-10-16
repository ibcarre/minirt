/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:47:23 by ibtihal           #+#    #+#             */
/*   Updated: 2025/10/16 16:11:57 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//https://vectrx.substack.com/p/lcg-xs-fast-gpu-rng

//LCG returns a number between (0 and 1)
double myrand(int seed) {
    //seed = seed * 1103515245 + 12345;
    //return((unsigned)(seed/65536) % 32768);
	//seed *= (seed + 195439) * (seed + 124395) * (seed + 845921);
	//return (seed / 4294967295);
	seed = seed * 747796405 + 2891336453;
	unsigned int result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
	return (((double)result / 4294967295));
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
	vec.y = myrand(seed);
	vec.z = myrand(seed);
	return (vec);
}

t_pos	random_vec_min_max(int seed, int min, int max)
{
	t_pos	vec;

	vec.x = rand_min_max(seed, min, max);
	vec.y = rand_min_max(seed, min, max);
	vec.z = rand_min_max(seed, min, max);
	return (vec);
}

//vec length squared parce que on est dans une range de 0 a 1 donc pas besoin de sqrt
//Pour avoir un vecteur unitaire random
t_pos	random_unit_vec(int seed)
{
	t_pos	vec;
	double	vec_length;

	vec = random_vec(seed);
	vec_length = vec_length_squared(vec);
	while (vec_length < 1e-6 && vec_length > 1)
	{
		vec = random_vec(seed);
		vec_length = vec_length_squared(vec);
	}
	return (vec_normalize(vec));
}

//retourne un vecteur unitaire random qui pointe dans la dir
t_pos	random_unit_vec_dir(int	seed, t_pos dir)
{
	t_pos	vec;

	vec = random_unit_vec(seed);
	if (dot_product(vec, dir) < 0)
		return (vec_init(-vec.x, -vec.y, -vec.z));
	return (vec);
}