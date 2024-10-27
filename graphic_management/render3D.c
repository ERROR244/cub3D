/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:04 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:57:42 by ksohail-         ###   ########.fr       */
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

unsigned int	get_texture_line(t_window *window, t_img *img,
		double wall_hit_x, int wall_height, int current_y)
{
	unsigned int	color;
	double			texture_y;
	int				texture_x;
	int				max_height;

	texture_x = (int)(wall_hit_x * SIZE) % SIZE;
	max_height = window->window_hight * 2;
	if (wall_height > max_height)
		wall_height = max_height;
	texture_y = ((double)current_y / wall_height) * SIZE;
	texture_y = fmax(0, fmin(texture_y, SIZE - 1));
	color = git_tpixel(img, texture_x, (int)texture_y);
	return (color);
}

int	draw_rect(t_window *window, int x, int y, int width, int height, t_img *img,
		double wall_hit_x)
{
	unsigned int	color;
	int				*f;
	int				*c;
	int				ret;
	int				i;
	int				j;

	i = 0;
	ret = 0;
	f = window->map->floor_color;
	c = window->map->ceiling_color;
	while (i < width && ret == 0)
	{
		j = 0;
		while (j < y && ret == 0)
		{
			ret = my_mlx_pixel_put(window, x + i, j, create_trgb(0, c[0], c[1],
						c[2]));
			j++;
		}
		j = 0;
		while (j < height && ret == 0)
		{
			color = get_texture_line(window, img, wall_hit_x, height, j);
			ret = my_mlx_pixel_put(window, x + i, y + j, color);
			j++;
		}
		while (j < window->window_hight && ret == 0)
		{
			ret = my_mlx_pixel_put(window, x + i, y + j, create_trgb(0, f[0],
						f[1], f[2]));
			j++;
		}
		i++;
	}
	return (ret);
}

int	render3d(t_window *window, int ret, int i)
{
	double	wall3dhight;
	double	displane;
	double	distance;
	double	wall_hit_x;
	double	max_height;
	t_img	*img;

	while (++i < window->rays && ret == 0)
	{
		distance = window->ray[i].distance * cos(window->ray[i].ray_a
				- window->pa);
		distance = fmax(distance, 0.1);
		displane = (window->window_width / 2) / tan(FOV_ANGLE / 2);
		wall3dhight = (window->tile_size / distance) * displane;
		max_height = window->window_hight * 2;
		if (wall3dhight > max_height)
			wall3dhight = max_height;
		img = window->ray[i].img;
		if (window->ray[i].washitver)
			wall_hit_x = fmod(window->ray[i].ray_hit_y, window->tile_size)
				/ window->tile_size;
		else
			wall_hit_x = fmod(window->ray[i].ray_hit_x, window->tile_size)
				/ window->tile_size;
		ret = draw_rect(window, round(i * window->wall_wigth),
				round((window->window_hight / 2) - (wall3dhight / 2)),
				round(window->wall_wigth), round(wall3dhight), img, wall_hit_x);
	}
	return (ret);
}
