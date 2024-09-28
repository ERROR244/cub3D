#include "../include/cub.h"

unsigned int get_color_from_img(t_window *window, void *img, int x, int y)
{
	unsigned int color;

	window->texture->img = img;
	window->texture->addr = mlx_get_data_addr(window->texture->img, &window->texture->bits_per_pixel, &window->texture->line_length, &window->texture->endian);
	if (window->texture->addr == NULL) {
	    fprintf(stderr, "Failed to get image data address.\n");
	    exit(EXIT_FAILURE);
	}
	color = git_tpixel(window, x % SIZE, y % SIZE);
	return (color);
}

int draw_rect(t_window *window, int x, int y, int width, int height, void *img)
{
	unsigned int color;
	int		ret;
    int		i;
    int		j;
	int 	k;

	k = 0;
	i = 0;
	ret = 0;
	(void)img;
    while (i < width && ret == 0)
    {
		j = 0;
		k = 0;
        while (j < height && ret == 0)
        {
			color = get_color_from_img(window, img, x + i, y + j);
			ret = my_mlx_pixel_put(window, x + i, y + j, color);
			j++;
			k += 2;
		}
		i++;
    }
	return (ret);
}

int render3d(t_window *window)
{
	double	wall3dhight;
	double	displane;
	double	distance;
	void	*img;
	int 	ret;
	int 	i;

	i = 0;
	ret = 0;
	clear_image(window, window->window_width, window->window_hight, 0x424242);
	while (i < window->rays && ret == 0)
	{
		distance = window->ray[i].distance * cos(window->ray[i].ray_a - window->pa);
		displane = (window->window_width / 2) / tan(FOV_ANGLE / 2);
		wall3dhight = (window->TILE_SIZE / distance) * displane;
		if (window->ray[i].washitver && window->ray[i].is_ray_looking_right)
			img = window->map->img_no;
		else if (window->ray[i].washitver && window->ray[i].is_ray_looking_left)
			img = window->map->img_so;
		if (!window->ray[i].washitver && window->ray[i].is_ray_looking_up)
			img = window->map->img_we;
		else if (!window->ray[i].washitver && window->ray[i].is_ray_looking_down)
			img = window->map->img_ea;
		if (window->ray[i].door_hit == true)
			img = window->map->door;
		draw_rect(window,
				  round(i * window->wall_wigth),
				  round((window->window_hight / 2) - (wall3dhight / 2)),
				  round(window->wall_wigth),
				  round(wall3dhight),
				  img
				  );
		i++;
	}
	return (ret);
}
