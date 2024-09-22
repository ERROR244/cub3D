#include "../include/cub.h"

int get_color_from_img(void *img)
{
	return (0);
}

int draw_rect(t_window *window, int x, int y, int width, int height, int color, void *img)
{
	int		ret;
    int		i;
    int		j;

	i = 0;
	ret = 0;
	(void)img;
    while (i < width && ret == 0)
    {
		j = 0;
        while (j < height && ret == 0)
        {
			// color = get_color_from_img(img);
			ret = my_mlx_pixel_put(window, x + i, y + j, color);
            // ret = mlx_pixel_put(window->mlx, window->window, x + i, y + j, 0xFFFFFF);
			j++;
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
	int 	color;
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

		color = 0x424242;
		if (window->ray[i].washitver && window->ray[i].is_ray_looking_right)
		{
			img = window->map->img_no;
			color = 0x1BFF1B;
		}
		else if (window->ray[i].washitver && window->ray[i].is_ray_looking_left)
		{
			img = window->map->img_so;
			color = 0xCCCCCC;
		}
		if (!window->ray[i].washitver && window->ray[i].is_ray_looking_up)
		{
			img = window->map->img_we;
			color = 0xFF0000;
		}
		else if (!window->ray[i].washitver && window->ray[i].is_ray_looking_down)
		{
			img = window->map->img_ea;
			color = 0x0000FF ;
		}
		if (window->ray[i].door_hit == true)
		{
			img = window->map->door;
			color = 0x000000;
		}
		draw_rect(window,
				  round(i * window->wall_wigth),
				  round((window->window_hight / 2) - (wall3dhight / 2)),
				  round(window->wall_wigth),
				  round(wall3dhight),
				  color,
				  img
				  );
		i++;
	}
	return (ret);
}
