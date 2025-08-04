/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:13:51 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/04 16:24:09 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argv, char **argc)
{
	//t_obj	*first;

	int	fd;
	if (argv != 2)
		return (1);
	fd = open(argc[1], O_RDONLY);
	//check si argc[1] est bien un fichier rt
	if (fd < 0)
		return (perror("Error"), 2);
	if (is_correct(fd) == -1)
			return (perror("Error"), 2);
	printf("DONE\n");
	// first = parsing(fd);
	// if (!first)
	// 	return (write(2, "Error, failed parsing\n", 22), 3);
}