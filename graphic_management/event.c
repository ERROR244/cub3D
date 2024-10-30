/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalil <khalil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:58 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/30 12:54:51 by khalil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	handle_rotate(t_window *window)
{
	if (window->move.rotate_right == 1)
	{
		window->pa += 0.09;
		if (window->pa > 2 * PI)
			window->pa -= 2 * PI;
	}
	else if (window->move.rotate_left == 1)
	{
		window->pa -= 0.09;
		if (window->pa < 0)
			window->pa += 2 * PI;
	}
	return (0);
}

int	handle_mouse(t_window *window, int x, int y)
{
	int	hold;

	mlx_mouse_get_pos(window->mlx, window->window, &x, &y);
	if (x > 0 && y > 0 && y < 900)
	{
		hold = x - window->mouse_x;
		mlx_mouse_get_pos(window->mlx, window->window, &window->mouse_x,
			&window->mouse_y);
		if (hold > 0)
		{
			window->pa += fft_abs(hold * 4) * 0.001;
			if (window->pa > 2 * PI)
				window->pa -= 2 * PI;
		}
		else if (hold < 0)
		{
			window->pa -= fft_abs(hold * 4) * 0.001;
			if (window->pa < 0)
				window->pa += 2 * PI;
		}
	}
	handle_mouse_2(window, x);
	return (0);
}

void	handle_mouse_2(t_window *window, int x)
{
	if (x == 0)
	{
		window->pa -= 0.04;
		if (window->pa < 0)
			window->pa += 2 * PI;
	}
	else if (x >= 1919)
	{
		window->pa += 0.04;
		if (window->pa < 0)
			window->pa -= 2 * PI;
	}
	if (window->change_fov_flag == false)
	{
		window->change_fov_flag = true;
		window->pa = get_spawninig_orientation(window->spawning_dir);
	}
}

int	key_press(int keycode, t_window *window)
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

int	key_release(int keycode, t_window *window)
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
