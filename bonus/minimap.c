/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:14:15 by moer-ret          #+#    #+#             */
/*   Updated: 2024/10/28 18:30:09 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	map_bounds_nor(t_map_bounds *bounds, double player_x, double player_y)
{
	bounds->xx = (int)(player_x) - MINI_MAP_SIZE;
	bounds->yy = (int)(player_y) - MINI_MAP_SIZE;
	if (bounds->xx < 0)
		bounds->xx = 0;
	if (bounds->yy < 0)
		bounds->yy = 0;
}

void	init_map_bounds(t_map_bounds *bounds, double player_x, double player_y)
{
	bounds->xx = (int)(player_x) - MINI_MAP_SIZE;
	bounds->yy = (int)(player_y) - MINI_MAP_SIZE;
	if (bounds->xx < 0)
	{
		bounds->x_start = 0;
		bounds->x_end = (int)(player_x) + MINI_MAP_SIZE - bounds->xx;
	}
	else
	{
		bounds->x_end = (int)(player_x) + MINI_MAP_SIZE;
		bounds->x_start = (int)(player_x) - MINI_MAP_SIZE;
	}
	if (bounds->yy < 0)
	{
		bounds->y_start = 0;
		bounds->y_end = (int)(player_y) + MINI_MAP_SIZE - bounds->yy;
	}
	else
	{
		bounds->y_end = (int)(player_y) + MINI_MAP_SIZE;
		bounds->y_start = (int)(player_y) - MINI_MAP_SIZE;
	}
	map_bounds_nor(bounds, player_x, player_y);
}

int	draw_remaining_squares(t_window *window, int start_x, int remaining)
{
	int	x;
	int	y;
	int	k;
	int	l;

	x = start_x;
	k = 0;
	while (k < remaining)
	{
		l = 0;
		y = 0;
		while (l < (MINI_MAP_SIZE * 2))
		{
			if (draw_map_square(window, x, y, 0x00FFFF) != 0)
				return (1);
			y += 16;
			l++;
		}
		x += 16;
		k++;
	}
	return (0);
}

int	draw_map_row(t_window *window, char *row, t_map_bounds *bounds,
	t_draw_pos *pos)
{
	int	j;
	int	y;

	j = bounds->x_start;
	y = 0;
	while (row[j] && j < bounds->x_end)
	{
		if (draw_map_square(window, pos->x, y,
				get_square_color(row[j])) != 0)
			return (1);
		j++;
		if (row[j] == '\0' || row[j] == '\n')
		{
			while (j <= (window->i + 4) && j <= bounds->x_end)
			{
				if (draw_map_square(window, pos->x, y, 0x00FFFF) != 0)
					return (1);
				y += 16;
				j++;
			}
			break ;
		}
		y += 16;
	}
	return (0);
}

int	draw_mini_map(t_window *window)
{
	t_map_bounds	bounds;
	t_draw_pos		pos;
	double			player_x;
	double			player_y;
	int				i;

	player_x = (double)(window->player_x / window->tile_size);
	player_y = (double)(window->player_y / window->tile_size);
	init_map_bounds(&bounds, player_x, player_y);
	player_x -= bounds.xx;
	player_y -= bounds.yy;
	pos.x = 0;
	i = bounds.y_start;
	while (window->map->map[i] && i < bounds.y_end)
	{
		if (draw_map_row(window, window->map->map[i], &bounds, &pos) != 0)
			return (1);
		pos.x += 16;
		i++;
	}
	if (i < bounds.y_end && draw_remaining_squares(window, pos.x,
			bounds.y_end - i) != 0)
		return (1);
	return (draw_mini_player(window, (player_y * 16),
			(player_x * 16), 0x00000));
}
