/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:18:09 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/28 12:05:21 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int draw_mini_squar(t_window *window, int y, int x, int color)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = 0;
	while (i < 10 && ret == 0)
	{
		j = 0;
		while (j < 10 && ret == 0)
		{
			// if (j < 2 || i < 2)
			// 	ret = mlx_pixel_put(window->mlx, window->window, x + i, y + j, 0x808080);
			// else
			ret = mlx_pixel_put(window->mlx, window->window, x + i, y + j, color);
			j++;
		}
		i++;
	}
	i = -2;
    double xx = (window->player_x / 32) * 10;
    double yy = (window->player_y / 32) * 10;
	while (i < 2 && ret == 0)
	{
		j = -2;
		while (j < 2 && ret == 0)
		{
			ret = mlx_pixel_put(window->mlx, window->window, xx + i, yy + j, 0x808080);
			j++;
		}
		i++;
	}
	return (ret);
}

int draw_mini_map(t_window *window)
{
	char **map;
	int i;
	int j;
	int x = 0;
	int y = 0;
	int ret;

	i = 0;
	ret = 0;
	map = window->map->map;
	while (map[i] && ret == 0)
	{
		j = 0;
		y = 0;
		while (map[i][j] && ret == 0)
		{
			if (map[i][j] == '0')
				ret = draw_mini_squar(window, x, y, 0xFFFFFF);
			else if (map[i][j] == '1' || map[i][j] == ' ')
				ret = draw_mini_squar(window, x, y, 0x000000);
			else if (map[i][j] == 'N')
				ret = draw_mini_squar(window, x, y, 0xFFFFFF);
			if (map[i][j + 1] == '\0')
			{
				while (j <= window->i)
				{
					ret = draw_mini_squar(window, x, y, 0x000000);
					y += 10;
					j++;
				}
				break ;
			}
			j++;
			y += 10;
		}
		x += 10;
		i++;
	}
	return (ret);
}