#include "../include/cub.h"

int	close_window(t_window *window)
{
	printf("Good game\n");
    exit_game(window);
	mlx_destroy_window(window->mlx, window->window);
	exit(EXIT_SUCCESS);
	return (0);
}

events get_event(int keycode)
{
	events event;

	event = none;
	if (keycode == 65363)
		event = moveRight;
	else if (keycode == 65362)
		event = moveForWard;
	else if (keycode == 65364)
		event = moveBackward;
	else if (keycode == 65361)
		event = moveLeft;
	else if (keycode == 100)
		event = viewRight;
	else if (keycode == 97)
		event = viewLeft;
	else if (keycode == 65307)
		event = escExit;
	return (event);
}

int handle_event1(events event, t_window *window, int x, int y)
{
	if (event == moveForWard)
	{
		x = (window->player_x) / window->TILE_SIZE;
		y = (window->player_y - 3) / window->TILE_SIZE;
		if (window->map->map[y][x] != '1')
			window->player_y -= 3;
	}
	else if (event == moveBackward)
	{
		x = (window->player_x) / window->TILE_SIZE;
		y = (window->player_y + 3) / window->TILE_SIZE;
		if (window->map->map[y][x] != '1')
			window->player_y += 3;
	}
	else if (event == moveRight)
	{
		x = (window->player_x + 3) / window->TILE_SIZE;
		y = (window->player_y) / window->TILE_SIZE;
		if (window->map->map[y][x] != '1')
			window->player_x += 3;
	}
	return (0);
}

int handle_event2(events event, t_window *window, int x, int y)
{
	if (event == moveLeft)
	{
		x = (window->player_x - 3) / window->TILE_SIZE;
		y = (window->player_y) / window->TILE_SIZE;
		if (window->map->map[y][x] != '1')
			window->player_x -= 3;
	}
	else if (event == viewRight)
	{
		window->pa += 0.1;
		if (window->pa > 2*PI)
			window->pa -= 2*PI;
	}
	else if (event == viewLeft)
	{
		window->pa -= 0.1;
		if (window->pa < 0)
			window->pa += 2*PI;
	}
	else if (event == escExit)
		close_window(window);
	return (0);
}

int	key_hook(int keycode, t_window *window)
{
	events event;
	int ret;

	mlx_clear_window(window->mlx, window->window);
	event = get_event(keycode);
	handle_event1(event, window, 0, 0);
	handle_event2(event, window, 0, 0);
	rays3D_cast(window);
	ret = render3d(window);
	// draw_map(window);
	return (ret);
}
