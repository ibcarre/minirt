/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:41:45 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/04 16:39:41 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	ft_isspace(char c)
{
	if (c == '\t' || (c > 10 && c < 14))
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}


char	*skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (&line[i]);
}
