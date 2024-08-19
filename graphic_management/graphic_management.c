#include "../include/cub.h"

int	key_hook(int keycode, t_window *w)
{
    // printf("%d \n", keycode);
	if (keycode == 65307)
		close_window(w);
	return (0);
}

int	close_window(t_window *window)
{
	int	i;

	i = 0;
	printf("Good game\n");
    exit_game(window);
	mlx_destroy_window(window->mlx, window->window);
	exit(EXIT_SUCCESS);
	return (0);
}

void	graphic_management(t_window *window)
{
	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, 500, 500, "cub3D");





	mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
}
