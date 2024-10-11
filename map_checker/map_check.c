/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:26 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/11 11:25:30 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// check texture

void	map_check(t_map *map, char **str, t_window *window)
{
	char	**lines;
	int		length;
	int		i;

	lines = str + 6;
	i = 0;
	check_characters(lines, window, 0, 0);
	is_the_map_surrounded_by_walls(lines);
	check_texture_and_color(map, str);
	length = array_size(map->map);
	map->array_length = malloc(sizeof(int ) * length);
	while (map->map[i])
	{
		map->array_length[i] = ft_strlen(map->map[i]);
		i++;
	}
	free_array(str);
	str = NULL;
}
