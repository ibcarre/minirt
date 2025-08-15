/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibtihal <ibtihal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:13:51 by ibtihal           #+#    #+#             */
/*   Updated: 2025/08/14 20:07:44 by ibtihal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argv, char **argc)
{
	t_obj	*first;

	int	fd;
	if (argv != 2)
		return (1);
	//check si argc[1] est bien un fichier rt
	fd = open(argc[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error"), 2);
	first = parsing(fd);
	if (!first)
		return (write(2, "Error, failed parsing\n", 22), 3);
	t_obj *temp = first;
	while(temp)
	{
		print_obj_param(temp);
		temp = temp->next;
	}
	free_objs(first);
}
