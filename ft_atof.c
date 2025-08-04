/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:33:59 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/04 16:30:36 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		*i++;
	if (str[*i] == '-')
	{
		*i++;
		*sign = -1;
		*test++;
	}
}

int	ft_atoi(char *str)
{
	long	res;
	int	i;
	long	test;
	int	sign;

	res = 0;
	i = 0;
	test = __INT_MAX__;
	get_sign(&sign, str, &i, &test);
	while (str[i])
	{
		while(str[i] && !is_digit(str[i]))
			i++;
		if (!str[i])
			break ;
		if (res * 10 + str[i] - '0' > test)
		{
			printf("WARNING : Higher than INT MAX. Value truncated\n");
			printf("If this is not the desired outcome, change the .rt file\n");
			break ;
		}
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

double	ft_atof(char *str)
{
	
}
