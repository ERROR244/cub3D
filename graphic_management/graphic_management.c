/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/13 10:34:32 by ksohail-         ###   ########.fr       */
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


int	put_img(t_window *window)
{
	if (window->move.rotate_right == 1 || window->move.rotate_left == 1)
		handle_rotate(window);
	if (window->move.right == 1 || window->move.left == 1)
		handle_lr_move(window, 0, 0);
	if (window->move.forward == 1 || window->move.backward == 1)
		handle_fb_move(window);
	rays_3d_cast(window);
	if (render3d(window, 0, -1) != 0);
		return (-1);
	draw_mini_map(window);
	handle_mouse(window);

	
	double playerx = (double)(window->player_x / window->TILE_SIZE);
	double playery = (double)(window->player_y / window->TILE_SIZE);
	int xx = (int)(playerx) - MINI_MAP_SIZE;
	int yy = (int)(playery) - MINI_MAP_SIZE;
	if (xx < 0)
		xx = 0;
	if (yy < 0)
		yy = 0;
	playerx -= xx;
	playery -= yy;
	dda_for_line(	((playerx * 32) + 3),
					((playery * 32) + 6),
					((playerx * 32) + 3) + cos(window->pa) * 30,
					((playery * 32) + 6) + sin(window->pa) * 30,
					window
				);			// direction

				
	mlx_clear_window(window->mlx, window->window);
	mlx_put_image_to_window(window->mlx, window->window, window->img->img, 0, 0);
	return (0);
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
	window->rays = window->window_width / window->wall_wigth;
	window->move.forward = 0;
	window->move.backward = 0;
	window->move.left = 0;
	window->move.right = 0;
	window->move.rotate_left = 0;
	window->move.rotate_right = 0;
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
			"./Textures/xpm/star_ship/starship_wall_north_HD.xpm", &width,
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


	
	mlx_hook(window->window, 17, 0L, close_window, window);
	mlx_hook(window->window, 02, 1L << 0, key_press, window);
	mlx_loop_hook(window->mlx, put_img, window);
	mlx_hook(window->window, 03, 1L << 1, key_release, window);

	
	
	
	
	mlx_loop(window->mlx);
}

	// draw_2D_map(window);