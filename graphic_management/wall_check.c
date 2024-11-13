/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/28 18:33:48 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	close_window(t_window *window)
{
	int	i;

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

bool	has_wall_at(long x, long y, t_window *window)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	map_grid_index_x = (int)(x / window->tile_size);
	map_grid_index_y = (int)(y / window->tile_size);
	if (x < 0 || x > window->i * window->tile_size || y < 0 || y > window->k
		* window->tile_size)
		return (false);
	if (window->map->line_size <= map_grid_index_x)
		return (false);
	return (window->map->map[map_grid_index_y][map_grid_index_x] == '0'
		|| window->map->map[map_grid_index_y][map_grid_index_x] == 'A'
		|| window->map->map[map_grid_index_y][map_grid_index_x] == 'N');
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

double	dis(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	fft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
