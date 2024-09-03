#include "../include/cub.h"

int draw_rect(t_window *window, int x, int y, int width, int height, int color)
{
	int ret;
    int i;
    int j;

	i = 0;
	ret = 0;
    while (i < width && ret == 0)
    {
		j = 0;
        while (j < height && ret == 0)
        {
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
		color = (window->ray[i].washitver) ? 0xB7B7B7 : 0xCCCCCC;
		draw_rect(window,
				  round(i * window->wall_wigth),
				  round((window->window_hight / 2) - (wall3dhight / 2)),
				  round(window->wall_wigth),
				  round(wall3dhight),
				  color
				  );
		i++;
	}
	return (ret);
}
