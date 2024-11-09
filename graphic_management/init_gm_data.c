/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gm_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/11/03 13:17:17 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_data(t_window *window, int width, int height)
{
	window->wall_wigth = 1;
	window->window_width = 1200;
	window->window_hight = 900;
	window->rays = window->window_width / window->wall_wigth;
	window->move.forward = 0;
	window->move.backward = 0;
	window->move.left = 0;
	window->move.right = 0;
	window->move.rotate_left = 0;
	window->move.rotate_right = 0;
	window->mouse_x = 0;
	window->mouse_y = 0;
	window->shoot = false;
	window->change_fov_flag = false;
	window->texture = malloc(sizeof(*(window->img)) * 5);
	window->mlx = mlx_init();
	init_texture(window, width, height);
	window->anm = malloc(sizeof(*(window->img)) * 4);
	init_texture_anm(window, 0, 0);
	init_anm(window);
	window->window = mlx_new_window(window->mlx, window->window_width,
			window->window_hight, "cub3D");
	window->ray = malloc(sizeof(*(window->ray)) * window->rays);
	window->img = malloc(sizeof(*(window->img)));
}

double	get_spawninig_orientation(t_orientation ori)
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

void	init_texture(t_window *window, int width, int height)
{
	window->texture[0].img = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_no, &width, &height);
	window->texture[0].sizex = width;
	window->texture[0].sizey = height;
	window->texture[1].img = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_so, &width, &height);
	window->texture[1].sizex = width;
	window->texture[1].sizey = height;
	window->texture[2].img = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_we, &width, &height);
	window->texture[2].sizex = width;
	window->texture[2].sizey = height;
	window->texture[3].img = mlx_xpm_file_to_image(window->mlx,
			window->map->texture_ea, &width, &height);
	window->texture[3].sizex = width;
	window->texture[3].sizey = height;
	window->texture[4].img = mlx_xpm_file_to_image(window->mlx,
			"./Textures/xpm/Door.xpm", &width, &height);
	window->texture[4].sizex = width;
	window->texture[4].sizey = height;
	if (!window->texture[0].img || !window->texture[1].img
		|| !window->texture[2].img || !window->texture[3].img
		|| !window->texture[4].img)
		exit_window_with_error(window, "bad game\n");
}

void	init_texture_anm(t_window *window, int sizex, int sizey)
{
	window->texture[0].addr = mlx_get_data_addr(window->texture[0].img,
			&window->texture[0].bits_per_pixel, &window->texture[0].line_length,
			&window->texture[0].endian);
	window->texture[1].addr = mlx_get_data_addr(window->texture[1].img,
			&window->texture[1].bits_per_pixel, &window->texture[1].line_length,
			&window->texture[1].endian);
	window->texture[2].addr = mlx_get_data_addr(window->texture[2].img,
			&window->texture[2].bits_per_pixel, &window->texture[2].line_length,
			&window->texture[2].endian);
	window->texture[3].addr = mlx_get_data_addr(window->texture[3].img,
			&window->texture[3].bits_per_pixel, &window->texture[3].line_length,
			&window->texture[3].endian);
	window->texture[4].addr = mlx_get_data_addr(window->texture[4].img,
			&window->texture[4].bits_per_pixel, &window->texture[4].line_length,
			&window->texture[4].endian);
	window->anm[0].img = mlx_xpm_file_to_image(window->mlx,
			"Textures/xpm/pis-0/pis-0.xpm", &sizex, &sizey);
	window->anm[1].img = mlx_xpm_file_to_image(window->mlx,
			"Textures/xpm/pis-0/pis-1.xpm", &sizex, &sizey);
	window->anm[2].img = mlx_xpm_file_to_image(window->mlx,
			"Textures/xpm/pis-0/pis-2.xpm", &sizex, &sizey);
	window->anm[3].img = mlx_xpm_file_to_image(window->mlx,
			"Textures/xpm/pis-0/pis-3.xpm", &sizex, &sizey);
}

void	init_anm(t_window *window)
{
	if (!window->texture[0].addr || !window->texture[1].addr
		|| !window->texture[2].addr || !window->texture[3].addr
		|| !window->texture[4].addr || !window->anm[0].img
		|| !window->anm[1].img || !window->anm[2].img || !window->anm[3].img)
		exit_window_with_error(window, "bad game\n");
	window->anm[0].addr = mlx_get_data_addr(window->anm[0].img,
			&window->anm[0].bits_per_pixel, &window->anm[0].line_length,
			&window->anm[0].endian);
	window->anm[1].addr = mlx_get_data_addr(window->anm[1].img,
			&window->anm[1].bits_per_pixel, &window->anm[1].line_length,
			&window->anm[1].endian);
	window->anm[2].addr = mlx_get_data_addr(window->anm[2].img,
			&window->anm[2].bits_per_pixel, &window->anm[2].line_length,
			&window->anm[2].endian);
	window->anm[3].addr = mlx_get_data_addr(window->anm[3].img,
			&window->anm[3].bits_per_pixel, &window->anm[3].line_length,
			&window->anm[3].endian);
	if (!window->anm[0].addr || !window->anm[1].addr || !window->anm[2].addr
		|| !window->anm[3].addr)
		exit_window_with_error(window, "bad game\n");
}
