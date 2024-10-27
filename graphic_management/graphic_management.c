/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:50:11 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

unsigned int	get_pixel_color(char *src_addr, int x, int y, int line_length,
		int bits_per_pixel)
{
	char	*pixel;

	pixel = src_addr + (y * line_length + x * (bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
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

void	put_anm_to_img(t_window *window, int index)
{
	unsigned int	color;
	int				x;
	int				y;
	int				i;

	x = 0;
	y = 0;
	i = index / 5;
	while (x < 512)
	{
		y = 0;
		while (y < 512)
		{
			color = get_pixel_color(window->anm[i].addr, x, y,
					window->anm[i].line_length, window->anm[i].bits_per_pixel);
			if (color != 0x000000)
				my_mlx_pixel_put(window, x + 410, y + 410, color);
			y++;
		}
		x++;
	}
}

int	put_img(t_window *window)
{
	static int	index;

	if (window->move.rotate_right == 1 || window->move.rotate_left == 1)
		handle_rotate(window);
	if (window->move.right == 1 || window->move.left == 1)
		handle_lr_move(window, 0, 0);
	if (window->move.forward == 1 || window->move.backward == 1)
		handle_fb_move(window);
	rays_3d_cast(window);
	if (render3d(window, 0, -1) != 0)
		close_window(window);
	draw_mini_map(window);
	handle_mouse(window);
	mlx_clear_window(window->mlx, window->window);
	put_anm_to_img(window, index);
	mlx_put_image_to_window(window->mlx, window->window, window->img->img, 0,
		0);
	if (window->shoot == true)
		index++;
	if (index >= 19)
		index = 0;
	else if (index != 0)
		index++;
	return (0);
}

void	graphic_management(t_window *window)
{
	window->minimap = 0.5;
	window->pa = get_spawninig_orientation(window->spawning_dir);
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
