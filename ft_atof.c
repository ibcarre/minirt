/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:33:59 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/13 12:15:12 by ibtihal          ###   ########.fr       */
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

int	ft_atoi(char **str)
{
	long	res;
	int	i;
	long	test;
	int	sign;

	res = 0;
	i = 0;
	test = __INT_MAX__;
	get_sign(&sign, *str, &i, &test);
	while (str[i])
	{
		if (!(*str)[i] || !is_digit((*str)[i]))
			break ;
		if (res * 10 + (*str)[i] - '0' > test)
		{
			printf("WARNING : Higher than INT MAX. Value truncated\n");
			printf("If this is not the desired outcome, change the .rt file\n");
			break ;
		}
		res = res * 10 + (*str)[i] - '0';
		i++;
	}
	*str = &((*str)[i]);
	return (res * sign);
}

int	intlen(int ent)
{
	int	len;

	len = 0 ;
	if (ent < 0)
		ent = ent * -1;
	while (ent > 10)
	{
		ent = ent/10;
		len++;
	}
	return (len + 1);
}

double	ft_atof(char **str, int *works)
{
	long	ent;
	int		dec;
	double	res;
	int		i;

	i = 0;
	ent = ft_atoi(str);
	while (is_digit((*str)[i]))
		i = i + 1;
	if (ft_isspace((*str)[i]) || !(*str)[i])
		return (ent);
	if ((*str)[i] && (*str)[i] != '.')
	{
		*works = 0;
		*str = &((*str)[i]);
		return (0);
	}
	i = i + 1;
	dec = ft_atoi(&((*str)[i]));
	ent = ent * pow(10, intlen(dec));
	res = ent + dec;
	*str = &((*str)[i]);
	res = res / pow(10, intlen(dec));
	return (res);
}
