/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:58 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:16:03 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	close_window(t_window *window)
{
	int i;

	i = 0;
	printf("Good game\n");
	exit_game(window);
	while (i < 4)
	{
		mlx_destroy_image(window->mlx, window->texture[i].img);
		mlx_destroy_image(window->mlx, window->anm[i++].img);
	}
	mlx_destroy_image(window->mlx, window->texture[i].img);
	mlx_destroy_image(window->mlx, window->img->img);
	free(window->texture);
	free(window->anm);
	free(window->img);
	free(window->ray);
	if (window->mlx && window->window)
        mlx_destroy_window(window->mlx, window->window);
    if (window->mlx)
	{
        mlx_destroy_display(window->mlx);
        free(window->mlx);
	}
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

int	get_tmpx_tmpy_fb(char c, t_window *window, events event)
{
	int	tmp;

	if (c == 'x')
		tmp = -5;
	else
		tmp = 10;
	if (c == 'x' && ((window->ray[window->rays / 2].is_ray_looking_right
				&& event == moveForWard) || (window->ray[window->rays
					/ 2].is_ray_looking_left && event == moveBackward)))
		tmp = 10;
	if (c == 'y' && ((window->ray[window->rays / 2].is_ray_looking_up
				&& event == moveForWard) || (window->ray[window->rays
					/ 2].is_ray_looking_down && event == moveBackward)))
		tmp = -5;
	return (tmp);
}

int	handle_fb_move(t_window *window)
{
	double x;
	double y;
	int	tmpx;
	int	tmpy;

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
		if (has_wall_at(x + ((x - window->player_x) * 6),
			y + ((y - window->player_y) * 6), window))
		{
			window->player_x = x;
			window->player_y = y;
		}
	}
	else
	{
		x = window->player_x + (cos(window->pa + (PI / 2)) * MSPEED);
		y = window->player_y + (sin(window->pa + (PI / 2)) * MSPEED);
		if (has_wall_at(x + ((x - window->player_x) * 6),
			y + ((y - window->player_y) * 6), window))
		{
			window->player_x = x;
			window->player_y = y;
		}
	}
	return (0);
}

int	handle_rotate(t_window *window)
{
	if (window->move.rotate_right == 1)
	{
		window->pa += 0.05;
		if (window->pa > 2 * PI)
			window->pa -= 2 * PI;
	}
	else if (window->move.rotate_left == 1)
	{
		window->pa -= 0.05;
		if (window->pa < 0)
			window->pa += 2 * PI;
	}
	return (0);
}

int fft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int handle_mouse(t_window *window)
{
	int x;
	int y;
	int hold;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(window->mlx, window->window, &x, &y);
	if (x > 0 && y > 0 && y < 900)
	{
		hold = x - window->mouse_x;
		mlx_mouse_get_pos(window->mlx, window->window, &window->mouse_x, &window->mouse_y);
		if (hold > 0)
		{
			window->pa += fft_abs(hold * 4) * 0.001;
			if (window->pa > 2*PI)
				window->pa -= 2*PI;
		}
		else if (hold < 0)
		{
			window->pa -= fft_abs(hold * 4) * 0.001;
			if (window->pa < 0)
				window->pa += 2*PI;
		}
	}
	if (x == 0)
	{
		window->pa -= 0.04;
		if (window->pa < 0)
			window->pa += 2*PI;
	}
	else if (x >= 1919)
	{
		window->pa += 0.04;
		if (window->pa < 0)
			window->pa -= 2*PI;
	}
	return (0);
}


int		key_press(int keycode, t_window *window)
{
	if (keycode == 119)
		window->move.forward = 1;
	else if (keycode == 115)
		window->move.backward = 1;
	else if (keycode == 97)
		window->move.right = 1;
	else if (keycode == 100)
		window->move.left = 1;
	else if (keycode == 65361)
		window->move.rotate_left = 1;
	else if (keycode == 65363)
		window->move.rotate_right = 1;
	else if (keycode == 32)
		handle_door(OpenClose, window);
	else if (keycode == 65307)
		close_window(window);
	else if (keycode == 101)
		window->shoot = true;
	return (0);
}

int		key_release(int keycode, t_window *window)
{
	if (keycode == 119)
		window->move.forward = 0;
	else if (keycode == 115)
		window->move.backward = 0;
	else if (keycode == 97)
		window->move.right = 0;
	else if (keycode == 100)
		window->move.left = 0;
	else if (keycode == 65361)
		window->move.rotate_left = 0;
	else if (keycode == 65363)
		window->move.rotate_right = 0;
	else if (keycode == 101)
		window->shoot = false;
	return (0);
}
