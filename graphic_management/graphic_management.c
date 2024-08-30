#include "../include/cub.h"

void	graphic_management(t_window *window)
{
	window->minimap = 0.2;
	window->pa = PI/2;
	window->wall_wigth = 1;
	window->window_width = 1400;
	window->window_hight = 900;
	window->rays = window->window_width / window->wall_wigth;
	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->window_width, window->window_hight, "cub3D");


	// mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 02, 1L<<0, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
	// draw_2D_map(window);
}
