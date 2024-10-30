/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalil <khalil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:04 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/29 18:46:13 by khalil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

unsigned int	git_tpixel(t_img *img, int x, int y)
{
	unsigned int	ret;
	char			*dst;

	ret = 0;
	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		ret = *(unsigned int *)dst;
	}
	return (ret);
}

unsigned int	get_texture_line(t_window *window, t_render render,
		int wall_height, int current_y)
{
	unsigned int	color;
	double			texture_y;
	int				texture_x;
	int				max_height;

	texture_x = (int)(render.wall_hit_x * SIZE) % SIZE;
	max_height = window->window_hight * 2;
	if (wall_height > max_height)
		wall_height = max_height;
	texture_y = ((double)current_y / wall_height) * SIZE;
	texture_y = fmax(0, fmin(texture_y, SIZE - 1));
	color = git_tpixel(render.img, texture_x, (int)texture_y);
	return (color);
}

int	draw_rect(t_window *window, t_render render)
{
	int	ret;
	int	i;
	int	j;

	i = -1;
	ret = 0;
	while (++i < render.width && ret == 0)
	{
		j = -1;
		while (++j < render.y && ret == 0)
			ret = my_mlx_pixel_put(window, render.x + i, j, create_trgb(0,
						window->map->ceiling_color));
		j = -1;
		while (++j < render.height && ret == 0)
		{
			ret = my_mlx_pixel_put(window, render.x + i, render.y + j,
					get_texture_line(window, render, render.height, j));
		}
		while (++j < window->window_hight && ret == 0)
			ret = my_mlx_pixel_put(window, render.x + i, render.y + j,
					create_trgb(0, window->map->floor_color));
	}
	return (ret);
}

int	render3d(t_window *window, int ret, int i)
{
	t_render	render;

	while (++i < window->rays && ret == 0)
	{
		window->dist = window->ray[i].distance * cos(window->ray[i].ray_a
				- window->pa);
		window->dist = fmax(window->dist, 0.1);
		window->disp = (window->window_width / 2) / tan(FOV_ANGLE / 2);
		window->wl3dh = (window->tile_size / window->dist) * window->disp;
		if (window->wl3dh > window->window_hight * 2)
			window->wl3dh = window->window_hight * 2;
		if (window->ray[i].washitver)
			render.wall_hit_x = fmod(window->ray[i].ray_hit_y,
					window->tile_size) / window->tile_size;
		else
			render.wall_hit_x = fmod(window->ray[i].ray_hit_x,
					window->tile_size) / window->tile_size;
		render.x = round(i * window->wall_wigth);
		render.y = round((window->window_hight / 2) - (window->wl3dh / 2));
		render.width = round(window->wall_wigth);
		render.height = round(window->wl3dh);
		render.img = window->ray[i].img;
		ret = draw_rect(window, render);
	}
	return (ret);
}
