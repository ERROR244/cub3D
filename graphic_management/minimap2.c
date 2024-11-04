/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalil <khalil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:27:04 by moer-ret          #+#    #+#             */
/*   Updated: 2024/10/30 16:57:58 by khalil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	draw_map_square(t_window *window, int x_pos, int y_pos, int color)
{
	return (draw_mini_squar(window, x_pos, y_pos, color));
}

int	draw_mini_squar(t_window *window, double y, double x, int color)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (i < 16 && ret == 0)
	{
		j = 0;
		while (j < 16 && ret == 0)
		{
			ret = my_mlx_pixel_put(window, x + i + 2, y + j + 2, color);
			j++;
		}
		i++;
	}
	return (ret);
}

int	draw_mini_player(t_window *window, double y, double x, int color)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (i < 6 && ret == 0)
	{
		j = 0;
		while (j < 6 && ret == 0)
		{
			ret = my_mlx_pixel_put(window, x + i + 2, y + j + 2, color);
			j++;
		}
		i++;
	}
	return (ret);
}

int	get_square_color(char map_char)
{
	if (map_char == '0' || map_char == 'P')
		return (0x0000FF);
	else if (map_char == 'D')
		return (0xFF0000);
	else if (map_char == 'A')
		return (0x00FF00);
	return (0x00FFFF);
}
