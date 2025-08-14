/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:33:59 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/14 19:34:43 by ibtihal          ###   ########.fr       */
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

int	get_signz(char *str)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (str[i] && str[i] != '-' && !is_digit(str[i]))
	{
		i = i + 1;
	}
	if (str[i] && str[i] == '-')
		sign = -1;
	return (sign);
}

int	ft_atoi(char **str)
{
	long	res;
	int		i;
	long	test;
	int		sign;

	res = 0;
	i = 0;
	test = __INT_MAX__;
	get_sign(&sign, *str, &i, &test);
	while ((*str)[i] && !ft_isspace((*str)[i]))
	{
		if ((*str)[i] == '.' || (*str)[i] == ',')
			break ;
		if (res * 10 + (*str)[i] - '0' > test || !is_digit((*str)[i]))
		{
			printf("WAR : Weird parsing. Moving on\n");
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
	int		sign;

	i = 0;
	sign = get_signz(*str);
	ent = ft_atoi(str);
	if (ft_isspace((*str)[i]) || !(*str)[i])
		return (ent);
	if ((*str)[i] && (*str)[i] != '.')
	{
		*str = &((*str)[i]);
		return (*works = 0, 0);
	}
	i = i + 1;
	*str = &((*str)[i]);
	dec = ft_atoi(str);
	ent = ent * pow(10, intlen(dec));
	if (intlen(dec) >= 6)
		*works = 0;
	res = ent + dec;
	res = res / pow(10, intlen(dec));
	return (res * sign);
}

/*
int main(int av, char **ac)
{
	int works;
	works = 1;
	printf("%f\n", ft_atof(&(ac[1]), &works));
	if (!works)
		printf("DOESNT WORK\n");
	printf("%s\n", ac[1]);
}*/