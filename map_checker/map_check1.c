/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:36 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:29:51 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_orientation	get_sdir(t_window *window, char c, int i, int j)
{
	window->player_x = j * window->tile_size;
	window->player_y = i * window->tile_size;
	if (c == 'N')
		return (North);
	if (c == 'S')
		return (South);
	if (c == 'E')
		return (East);
	if (c == 'W')
		return (West);
	return (None);
}

void	check_c(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != 'D')
		the_map_is_invalid();
}

void	check_characters(char **map, t_window *window, int i, int k)
{
	int	j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_c(map[i][j]);
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'W') && ++k >= 0)
			{
				map[i][j] = '0';
				window->spawning_dir = get_sdir(window, map[i][j], i, j);
			}
			j++;
			if (window->i < j)
				window->i = j;
		}
		i++;
	}
	if (k != 1)
		the_map_is_invalid();
	window->k = i;
}

void	is_the_map_surrounded_by_walls(char **ptr)
{
	char	**map;
	int		lines;
	int		x;
	int		y;

	x = 0;
	map = ptr;
	lines = array_size(map);
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if ((map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'D')
				&& surrounded_with_only_spaces_and_walls(map, x, y,
					lines) == false)
				the_map_is_invalid();
			y++;
		}
		x++;
	}
	check_map_end(map);
}
