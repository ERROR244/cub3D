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

	window->wall_wigth = 5;
	window->rays = window->i / window->wall_wigth;

	// // window->dirX = -1;
	// // window->dirY = 0;
	// // window->planeX = 0;
	// // window->planeY = 0.66;

	// mlx_loop_hook(window->mlx, draw_map, window);

	// mlx_key_hook(window->window, key_hook, window);
	// mlx_hook(window->window, 17, 0L, close_window, window);
    // mlx_loop(window->mlx);
	draw_2D_map(window);
}
