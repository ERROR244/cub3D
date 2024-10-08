/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/08 12:15:56 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	clear_image(t_window *window, int width, int height, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			my_mlx_pixel_put(window, x, y, color);
			x++;
		}
		y++;
	}
}

unsigned int	git_tpixel(t_window *window, int x, int y)
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
		dst = window->texture->addr + (y * window->texture->line_length + x
				* (window->texture->bits_per_pixel / 8));
		ret = *(unsigned int *)dst;
	}
	return (ret);
}

int	my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < window->window_width && y >= 0
		&& y < window->window_hight)
	{
		dst = window->img->addr + (y * window->img->line_length + x
				* (window->img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	return (0);
}

	// double playerx = (double)(window->player_x / window->TILE_SIZE);
	// double playery = (double)(window->player_y / window->TILE_SIZE);
	// int xx = (int)(playerx) - MINI_MAP_SIZE;
	// int yy = (int)(playery) - MINI_MAP_SIZE;
	// if (xx < 0)
	// 	xx = 0;
	// if (yy < 0)
	// 	yy = 0;
	// playerx -= xx;
	// playery -= yy;
	// dda_for_line(	((playerx * 32) + 3),
	// 				((playery * 32) + 6),
	// 				((playerx * 32) + 3) + cos(window->pa) * 30,
	// 				((playery * 32) + 6) + sin(window->pa) * 30,
	// 				window
	// 			);			// direction

int	put_img(t_window *window)
{
	int	ret;

	ret = 0;
	rays_3d_cast(window);
	clear_image(window, window->window_width, window->window_hight, 0x424242);
	ret = render3d(window, 0, -1);
	draw_mini_map(window);
	handle_mouse(window);
	if (window->update_waidow == true
		|| window->update_waidow_for_mouse == true)
	{
		mlx_clear_window(window->mlx, window->window);
		mlx_put_image_to_window(window->mlx, window->window, window->img->img,
			0, 0);
	}
	window->update_waidow = false;
	window->update_waidow_for_mouse = false;
	return (ret);
}

double	get_spawninig_orientation(orientation ori)
{
	double	pa;

	pa = 0.0;
	if (ori == North)
		pa = 3 * PI / 2;
	else if (ori == South)
		pa = PI / 2;
	else if (ori == West)
		pa = PI;
	return (pa);
}

void	init_data(t_window *window, int width, int height)
{
	window->update_waidow = true;
	window->update_waidow_for_mouse = true;
	window->rays = window->window_width / window->wall_wigth;
	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->window_width,
			window->window_hight, "cub3D");
	window->map->img_no = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_no, &width, &height);
	window->map->img_so = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_so, &width, &height);
	window->map->img_we = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_we, &width, &height);
	window->map->img_ea = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_ea, &width, &height);
	window->map->door = mlx_xpm_file_to_image(window->mlx,
			"./Textures/xpm/wonderland/wonderland_wall_base.xpm", &width,
			&height);
	if (!window->map->img_no || !window->map->img_so || !window->map->img_we
		|| !window->map->img_ea)
		the_textures_is_invalid();
	window->ray = malloc(sizeof(*(window->ray)) * window->rays);
	window->img = malloc(sizeof(*(window->img)));
	window->texture = malloc(sizeof(*(window->img)));
}

void	graphic_management(t_window *window)
{
	window->minimap = 0.5;
	window->pa = get_spawninig_orientation(window->spawning_dir);
	window->wall_wigth = 1;
	window->window_width = 1400;
	window->window_hight = 900;
	init_data(window, SIZE, SIZE);
	if (window->img == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for img.\n");
		exit(EXIT_FAILURE);
	}
	window->img->img = mlx_new_image(window->mlx, window->window_width,
			window->window_hight);
	if (window->img->img == NULL)
		exit_error("Failed to create image.\n");
	window->img->addr = mlx_get_data_addr(window->img->img,
			&window->img->bits_per_pixel, &window->img->line_length,
			&window->img->endian);
	if (window->img->addr == NULL)
		exit_error("Failed to get image data address.\n");
	put_img(window);
	mlx_loop_hook(window->mlx, put_img, window);
	mlx_hook(window->window, 02, 1L << 0, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
	mlx_loop(window->mlx);
}

	// mlx_hook(window->window, 6, 1L<<6, kkey_hook, window);
	// draw_2D_map(window);