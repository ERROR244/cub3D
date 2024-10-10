/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:58 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/10 16:14:09 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	close_window(t_window *window)
{
	printf("Good game\n");
	exit_game(window);
	mlx_destroy_window(window->mlx, window->window);
	exit(EXIT_SUCCESS);
	return (0);
}

void	open_close_d(char *c)
{
	if (*c == 'D')
		*c = 'A';
	else
		*c = 'D';
}

int	handle_door(events event, t_window *window)
{
	int	i;
	int	j;

	if (event == OpenClose)
	{
		window->update_waidow = true;
		j = (int)(window->player_x / window->TILE_SIZE);
		i = (int)(window->player_y / window->TILE_SIZE);
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
		else
			window->update_waidow = false;
	}
	return (0);
}

int	handle_fb_move(t_window *window)
{
	int x;
	int y;
	double scale;

	scale = 2;
	// if (window->ray[window->rays / 2].is_ray_looking_up
	// 	|| window->ray[window->rays / 2].is_ray_looking_right)
	// {
	// 	printf("HERE------------------------\n");
	// 	scale = 2;
	// }
	// if ((window->ray[window->rays / 2].is_ray_looking_left
	// 	&& window->ray[window->rays / 2].is_ray_looking_up)
	// 	|| (window->ray[window->rays / 2].is_ray_looking_left
	// 	&& window->ray[window->rays / 2].is_ray_looking_up))
	// {
	// 	scale = 10;
	// 	printf("there>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	// }
	if (window->move.forward == 1)
	{
		window->update_waidow = true;
		x = (window->player_x + (cos(window->pa) * MSPEED * 1));
		y = (window->player_y + (sin(window->pa) * MSPEED * 1));
		if (!has_wall_at(x + ((x - window->player_x) * scale), window->player_y, window))
			window->player_x = x;
		if (!has_wall_at(window->player_x, y + ((y - window->player_y) * scale), window))
			window->player_y = y;
		if (window->player_x != x && window->player_y != y)
			window->update_waidow = false;
	}
	else if (window->move.backward == 1)
	{
		window->update_waidow = true;
		x = (window->player_x + (cos(window->pa) * MSPEED * -1));
		y = (window->player_y + (sin(window->pa) * MSPEED * -1));
		if (!has_wall_at(x + ((x - window->player_x) * scale), window->player_y, window))
			window->player_x = x;
		if (!has_wall_at(window->player_x, y + ((y - window->player_y) * scale), window))
			window->player_y = y;
		if (window->player_x != x && window->player_y != y)
			window->update_waidow = false;
	}
	return (0);
}

int	handle_rotate(t_window *window)
{
	if (window->move.rotate_right == 1)
	{
		window->update_waidow = true;
		window->pa += 0.05;
		if (window->pa > 2 * PI)
			window->pa -= 2 * PI;
	}
	else if (window->move.rotate_left == 1)
	{
		window->update_waidow = true;
		window->pa -= 0.05;
		if (window->pa < 0)
			window->pa += 2 * PI;
	}
	return (0);
}

int	handle_mouse(t_window *window)
{
	int	x;
	int	y;
	int	diff;
	static int a = 0;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(window->mlx, window->window, &x, &y);
	diff = window->mouse_x - x;
	mlx_mouse_get_pos(window->mlx, window->window, &window->mouse_x,
		&window->mouse_y);
	window->update_waidow_for_mouse = true;
	if (diff > 0)
		window->pa += diff * 0.005;
	else if (diff < 0)
		window->pa += diff * 0.005;
	else
		window->update_waidow_for_mouse = false;
	if (window->pa < 0)
		window->pa += TWO_PI;
	else if (window->pa > TWO_PI)
		window->pa = 0;
	if (a++ == 0)
		window->pa = get_spawninig_orientation(window->spawning_dir);
	return (0);
}

int		key_press(int keycode, t_window *window)
{
	if (keycode == 119)
		window->move.forward = 1;
	else if (keycode == 115)
		window->move.backward = 1;
	else if (keycode == 97)
		window->move.left = 1;
	else if (keycode == 100)
		window->move.right = 1;
	else if (keycode == 65361)
		window->move.rotate_left = 1;
	else if (keycode == 65363)
		window->move.rotate_right = 1;
	else if (keycode == 32)
		handle_door(OpenClose, window);
	else if (keycode == 65307)
		close_window(window);
	return (0);
}

int		key_release(int keycode, t_window *window)
{
	if (keycode == 119)
		window->move.forward = 0;
	else if (keycode == 115)
		window->move.backward = 0;
	else if (keycode == 97)
		window->move.left = 0;
	else if (keycode == 100)
		window->move.right = 0;
	else if (keycode == 65361)
		window->move.rotate_left = 0;
	else if (keycode == 65363)
		window->move.rotate_right = 0;
	return (0);
}
