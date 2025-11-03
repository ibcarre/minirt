/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:33:59 by ibtihal           #+#    #+#             */
/*   Updated: 2025/11/03 16:31:59 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	get_sign(int *sign, char *str, int *i, long *test)
{
	*sign = 1;
	while (str[*i] && str[*i] != '-' && !is_digit(str[*i]))
	{
		*i = *i + 1;
	}
	if (str[*i] && str[*i] == '-')
	{
		*i = *i + 1;
		*sign = -1;
		*test = *test + 1;
	}
}
