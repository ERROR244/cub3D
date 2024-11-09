/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:36 by ksohail-          #+#    #+#             */
/*   Updated: 2024/11/03 13:12:28 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_orientation	get_sdir(t_window *window, char c, int i, int j)
{
	window->player_x = j * window->tile_size + 5;
	window->player_y = i * window->tile_size + 5;
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

int	check_c(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ' && c != 'D')
		return (-1);
	return (1);
}

int	check_characters(char **map, t_window *window, int i, int k)
{
	int	j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_c(map[i][j]) == -1)
				return (-1);
			if ((map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
					|| map[i][j] == 'W') && ++k >= 0)
			{
				window->spawning_dir = get_sdir(window, map[i][j], i, j);
				map[i][j] = 'N';
			}
			j++;
			if (window->i < j)
				window->i = j;
		}
		i++;
	}
	if (k != 1)
		return (-1);
	window->k = i;
	return (1);
}

int	is_the_map_surrounded_by_walls(char **ptr)
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
				return (-1);
			y++;
		}
		x++;
	}
	check_map_end(map);
	return (1);
}
