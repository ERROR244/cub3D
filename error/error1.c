/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 18:34:54 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	invalid_file_name1(void)
{
	printf("Error\n		invalid file name\n");
	exit(EXIT_FAILURE);
}

void	invalid_file(void)
{
	printf("Error\n		invalid file\n");
	exit(EXIT_FAILURE);
}

void	invalid_arg(void)
{
	printf("Error\n		the number of argument is not 2\n");
	exit(EXIT_FAILURE);
}

void	the_map_is_cutted_slices(char *ptr, char *str, int fd)
{
	free(str);
	free(ptr);
	ptr = get_next_line(fd);
	while (ptr)
	{
		free(ptr);
		ptr = get_next_line(fd);
	}
	printf("Error\n		the map is cutted slices\n");
	exit(EXIT_FAILURE);
}

int	invalid_color(t_map *map)
{
	if (!map->ceiling_color || !map->floor_color)
	{
		if (map->ceiling_color)
			free(map->ceiling_color);
		if (map->floor_color)
			free(map->floor_color);
		if (map->texture_no)
			free(map->texture_no);
		if (map->texture_so)
			free(map->texture_so);
		if (map->texture_we)
			free(map->texture_we);
		if (map->texture_ea)
			free(map->texture_ea);
		return (-1);
	}
	return (1);
}
