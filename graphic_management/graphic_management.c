/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/25 11:50:13 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

unsigned int get_pixel_color(char *src_addr, int x, int y, int line_length, int bits_per_pixel)
{
    char *pixel = src_addr + (y * line_length + x * (bits_per_pixel / 8));
    return *(unsigned int *)pixel;
}

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
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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

void put_anm_to_img(t_window *window, int index)
{
	unsigned int color;
	int x = 0;
	int y = 0;
	int i;

	i = 0;
	if (index < 3)
		i = 0;
	else if (index < 6)
		i = 1;
	else if (index < 9)
		i = 2;
	else if (index < 12)
		i = 3;
	while (x < 512)
	{
		y = 0;
		while (y < 512)
		{
			color = get_pixel_color(window->anm[i].addr, x, y, window->anm[i].line_length, window->anm[i].bits_per_pixel);
			if (color != 0x000000)
				my_mlx_pixel_put(window, x + 410, y + 410, color);
			y++;
		}
		x++;
	}
}


int	put_img(t_window *window)
{
	static int index;
	if (window->move.rotate_right == 1 || window->move.rotate_left == 1)
		handle_rotate(window);
	if (window->move.right == 1 || window->move.left == 1)
		handle_lr_move(window, 0, 0);
	if (window->move.forward == 1 || window->move.backward == 1)
		handle_fb_move(window);
	rays_3d_cast(window);
	if (render3d(window, 0, -1) != 0)
		return (-1);
	draw_mini_map(window);
	handle_mouse(window);

	
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
				
	mlx_clear_window(window->mlx, window->window);
	put_anm_to_img(window, index);
	mlx_put_image_to_window(window->mlx, window->window, window->img->img, 0, 0);
	if (window->shoot == true)
		index++;
	if (index > 12)
		index = 0;
	else if (index != 0)
		index++;
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
	window->shoot = false;
	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->window_width,
			window->window_hight, "cub3D");
	window->ray = malloc(sizeof(*(window->ray)) * window->rays);
	window->img = malloc(sizeof(*(window->img)));
	window->texture = malloc(sizeof(*(window->img)) * 5);
	window->anm = malloc(sizeof(*(window->img)) * 4);
	init_texture(window, width, height);
	init_anm(window);
}

void init_texture(t_window *window, int width, int height)
{
	window->texture[0].img = mlx_xpm_file_to_image(window->mlx, window->map->texture_no, &width, &height);
	window->texture[1].img = mlx_xpm_file_to_image(window->mlx, window->map->texture_so, &width, &height);
	window->texture[2].img = mlx_xpm_file_to_image(window->mlx, window->map->texture_we, &width, &height);
	window->texture[3].img = mlx_xpm_file_to_image(window->mlx, window->map->texture_ea, &width, &height);
	window->texture[4].img =  mlx_xpm_file_to_image(window->mlx, "./Textures/xpm/star_ship/starship_wall_north_HD.xpm", &width, &height);
	if (!window->texture[0].img || !window->texture[1].img || !window->texture[2].img || !window->texture[3].img || !window->texture[4].img)
		the_textures_is_invalid();

	window->texture[0].addr = mlx_get_data_addr(window->texture[0].img, &window->texture[0].bits_per_pixel, &window->texture[0].line_length, &window->texture[0].endian);
	window->texture[1].addr = mlx_get_data_addr(window->texture[1].img, &window->texture[1].bits_per_pixel, &window->texture[1].line_length, &window->texture[1].endian);
	window->texture[2].addr = mlx_get_data_addr(window->texture[2].img, &window->texture[2].bits_per_pixel, &window->texture[2].line_length, &window->texture[2].endian);
	window->texture[3].addr = mlx_get_data_addr(window->texture[3].img, &window->texture[3].bits_per_pixel, &window->texture[3].line_length, &window->texture[3].endian);
	window->texture[4].addr = mlx_get_data_addr(window->texture[4].img, &window->texture[4].bits_per_pixel, &window->texture[4].line_length, &window->texture[4].endian);
	if (!window->texture[0].addr || !window->texture[1].addr || !window->texture[2].addr || !window->texture[3].addr || !window->texture[4].addr)
		the_textures_is_invalid();
}

void init_anm(t_window *window)
{
	int sizex;
	int sizey;

	sizex = 512;
	sizey = 512;
	window->anm[0].img = mlx_xpm_file_to_image(window->mlx, "pis-0/pis-0.xpm", &sizex, &sizey);
	window->anm[1].img = mlx_xpm_file_to_image(window->mlx, "pis-0/pis-1.xpm", &sizex, &sizey);
	window->anm[2].img = mlx_xpm_file_to_image(window->mlx, "pis-0/pis-2.xpm", &sizex, &sizey);
	window->anm[3].img = mlx_xpm_file_to_image(window->mlx, "pis-0/pis-3.xpm", &sizex, &sizey);
	if (!window->anm[0].img || !window->anm[1].img || !window->anm[2].img || !window->anm[3].img)
		the_textures_is_invalid();

	window->anm[0].addr = mlx_get_data_addr(window->anm[0].img, &window->anm[0].bits_per_pixel, &window->anm[0].line_length, &window->anm[0].endian);
	window->anm[1].addr = mlx_get_data_addr(window->anm[1].img, &window->anm[1].bits_per_pixel, &window->anm[1].line_length, &window->anm[1].endian);
	window->anm[2].addr = mlx_get_data_addr(window->anm[2].img, &window->anm[2].bits_per_pixel, &window->anm[2].line_length, &window->anm[2].endian);
	window->anm[3].addr = mlx_get_data_addr(window->anm[3].img, &window->anm[3].bits_per_pixel, &window->anm[3].line_length, &window->anm[3].endian);
	if (!window->anm[0].addr || !window->anm[1].addr || !window->anm[2].addr || !window->anm[3].addr)
		the_textures_is_invalid();
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
		exit_error("Failed to allocate memory for img.\n");
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