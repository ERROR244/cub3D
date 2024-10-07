/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:26 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 16:59:21 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

// check texture

void	map_check(t_map *map, char **str, t_window *window)
{
	char	**lines;

	lines = str + 6;
	check_characters(lines, window, 0, 0);
	is_the_map_surrounded_by_walls(lines);
	check_texture_and_color(map, str);
	free_array(str);
	str = NULL;
}
