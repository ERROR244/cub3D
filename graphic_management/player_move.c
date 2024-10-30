/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalil <khalil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:58 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/30 16:54:42 by khalil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	open_close_d(char *c)
{
	if (*c == 'D')
		*c = 'A';
	else
		*c = 'D';
}

int	handle_door(t_events event, t_window *window)
{
	int	i;
	int	j;

	if (event == OpenClose)
	{
		j = (int)(window->player_x / window->tile_size);
		i = (int)(window->player_y / window->tile_size);
		if (window->map->map[i + 1][j] && (window->map->map[i + 1][j] == 'D'
				|| window->map->map[i + 1][j] == 'A'))
			open_close_d(&window->map->map[i + 1][j]);
		else if (window->map->map[i][j + 1] && (window->map->map[i][j
				+ 1] == 'D' || window->map->map[i][j + 1] == 'A'))
			open_close_d(&window->map->map[i][j + 1]);
		else if (i - 1 >= 0 && (window->map->map[i - 1][j] == 'D'
			|| window->map->map[i - 1][j] == 'A'))
			open_close_d(&window->map->map[i - 1][j]);
		else if (j - 1 >= 0 && (window->map->map[i][j - 1] == 'D'
			|| window->map->map[i][j - 1] == 'A'))
			open_close_d(&window->map->map[i][j - 1]);
	}
	return (0);
}

int	get_tmpx_tmpy_fb(char c, t_window *window, t_events event)
{
	int	tmp;
	int	a;
	int	b;

	a = 5;
	b = 8;
	if (c == 'x')
		tmp = -a;
	else
		tmp = b;
	if (c == 'x' && ((window->ray[window->rays / 2].is_ray_looking_right
				&& event == moveForWard) || (window->ray[window->rays
					/ 2].is_ray_looking_left && event == moveBackward)))
		tmp = b;
	if (c == 'y' && ((window->ray[window->rays / 2].is_ray_looking_up
				&& event == moveForWard) || (window->ray[window->rays
					/ 2].is_ray_looking_down && event == moveBackward)))
		tmp = -a;
	return (tmp);
}

int	handle_fb_move(t_window *window)
{
	double	x;
	double	y;
	int		tmpx;
	int		tmpy;

	if (window->move.forward == 1)
	{
		x = window->player_x + (cos(window->pa) * MSPEED);
		y = window->player_y + (sin(window->pa) * MSPEED);
		tmpx = get_tmpx_tmpy_fb('x', window, moveForWard);
		tmpy = get_tmpx_tmpy_fb('y', window, moveForWard);
	}
	else
	{
		x = window->player_x - (cos(window->pa) * MSPEED);
		y = window->player_y - (sin(window->pa) * MSPEED);
		tmpx = get_tmpx_tmpy_fb('x', window, moveBackward);
		tmpy = get_tmpx_tmpy_fb('y', window, moveBackward);
	}
	if (has_wall_at(x + tmpx, window->player_y, window))
		window->player_x = x;
	if (has_wall_at(window->player_x, y + tmpy, window))
		window->player_y = y;
	return (0);
}

int	handle_lr_move(t_window *window, double x, double y)
{
	if (window->move.right == 1)
	{
		x = window->player_x + (cos(window->pa - (PI / 2)) * MSPEED);
		y = window->player_y + (sin(window->pa - (PI / 2)) * MSPEED);
		if (has_wall_at(x + ((x - window->player_x) * 6), y + ((y
						- window->player_y) * 6), window))
		{
			window->player_x = x;
			window->player_y = y;
		}
	}
	else
	{
		x = window->player_x + (cos(window->pa + (PI / 2)) * MSPEED);
		y = window->player_y + (sin(window->pa + (PI / 2)) * MSPEED);
		if (has_wall_at(x + ((x - window->player_x) * 6), y + ((y
						- window->player_y) * 6), window))
		{
			window->player_x = x;
			window->player_y = y;
		}
	}
	return (0);
}
