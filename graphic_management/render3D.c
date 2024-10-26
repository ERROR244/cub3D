/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:02:04 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/25 15:25:06 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

unsigned int	get_color_from_img(t_window *window, void *img, int x, int y)
{
	unsigned int	color;

	window->texture->img = img;
	window->texture->addr = mlx_get_data_addr(window->texture->img,
			&window->texture->bits_per_pixel, &window->texture->line_length,
			&window->texture->endian);
	if (window->texture->addr == NULL)
		exit_error("Failed to get image data address.\n");
	color = git_tpixel(window, x % SIZE, y % SIZE);
	return (color);
}

unsigned int get_texture_line(t_window *window, void *img, double wall_hit_x, int wall_height, int current_y)
{
    unsigned int color;
    double texture_y;
    
    window->texture->img = img;
    window->texture->addr = mlx_get_data_addr(window->texture->img,
        &window->texture->bits_per_pixel, &window->texture->line_length,
        &window->texture->endian);
    if (window->texture->addr == NULL)
        exit_error("Failed to get image data address.\n");
    int texture_x = (int)(wall_hit_x * SIZE) % SIZE;
    int max_height = window->window_hight * 2;
    if (wall_height > max_height)
        wall_height = max_height;
    texture_y = ((double)current_y / wall_height) * SIZE;
    texture_y = fmax(0, fmin(texture_y, SIZE - 1));
    color = git_tpixel(window, texture_x, (int)texture_y);
    return (color);
}

int draw_rect(t_window *window, int x, int y, int width, int height, void *img, double wall_hit_x)
{
    unsigned int color;
    int *floor_color;
    int *ceiling_color;
    int ret;
    int i;
    int j;
    
    i = 0;
    ret = 0;
    floor_color = window->map->floor_color;
    ceiling_color = window->map->ceiling_color;
    
    while (i < width && ret == 0)
    {
        j = 0;
        while (j < y && ret == 0)
        {
            ret = my_mlx_pixel_put(window, x + i, j, 
                0xFBCF67);
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
            ret = my_mlx_pixel_put(window, x + i, y + j, 
               0x964B00);
            j++;
        }
        i++;
    }
    return (ret);
}

int render3d(t_window *window, int ret, int i)
{
    double wall3dhight;
    double displane;
    double distance;
    void *img;
    
    while (++i < window->rays && ret == 0)
    {
        distance = window->ray[i].distance * cos(window->ray[i].ray_a - window->pa);
        distance = fmax(distance, 0.1);
        displane = (window->window_width / 2) / tan(FOV_ANGLE / 2);
        wall3dhight = (window->TILE_SIZE / distance) * displane;
        double max_height = window->window_hight * 2;
        if (wall3dhight > max_height)
            wall3dhight = max_height;
        img = window->ray[i].img;
        double wall_hit_x;
        if (window->ray[i].washitver)
            wall_hit_x = fmod(window->ray[i].ray_hit_y, window->TILE_SIZE) / window->TILE_SIZE;
        else
            wall_hit_x = fmod(window->ray[i].ray_hit_x, window->TILE_SIZE) / window->TILE_SIZE;
        ret = draw_rect(window, 
            round(i * window->wall_wigth),
            round((window->window_hight / 2) - (wall3dhight / 2)),
            round(window->wall_wigth),round(wall3dhight), 
            img, wall_hit_x);
    }
    return (ret);
}
