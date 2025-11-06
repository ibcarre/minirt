/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 04:21:44 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/06 15:49:25 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_obj	*get_amlight(t_vars mlx)
{
	while (mlx.first)
	{
		if (mlx.first->type == A_LIGHT)
			return (mlx.first);
		mlx.first = mlx.first->next;
	}
	return (NULL);
}
