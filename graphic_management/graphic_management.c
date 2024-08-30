#include "../include/cub.h"

double to_rad(double deg)
{
	return (deg * (PI / 180.0));
}

double to_deg(double rad)
{
	return (rad * (180.0 / PI));
}

void	graphic_management(t_window *window)
{
	// window->mlx = mlx_init();
	// window->window = mlx_new_window(window->mlx, 1400, 900, "cub3D");

	window->minimap = 0.2;
	window->pa = PI/2;
	window->wall_wigth = 1;
	window->window_width = 1400;
	window->window_hight = 900;
	window->rays = window->window_width / window->wall_wigth;
	// printf("%d\n", window->rays);


	// mlx_key_hook(window->window, key_hook, window);
	// mlx_hook(window->window, 17, 0L, close_window, window);
    // mlx_loop(window->mlx);
	draw_2D_map(window);
}
