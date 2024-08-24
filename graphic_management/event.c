#include "../include/cub.h"

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
	// else if (keycode == 119)
	// 	event = viewUp;
	// else if (keycode == 115)
	// 	event = viewDown;
	else if (keycode == 65307)
		event = escExit;
	return (event);
}

int handle_event(events event, t_window *window)
{
	int x;
	int y;
	if (event == moveForWard)
	{
		x = (window->player_x) / 32;
		y = (window->player_y - 10) / 32;
		if (window->map->map[y][x] != '1')
			window->player_y -= 10;
	}
	else if (event == moveBackward)
	{
		x = (window->player_x) / 32;
		y = (window->player_y + 10) / 32;
		if (window->map->map[y][x] != '1')
			window->player_y += 10;
	}
	else if (event == moveRight)
	{
		x = (window->player_x + 10) / 32;
		y = (window->player_y) / 32;
		if (window->map->map[y][x] != '1')
			window->player_x += 10;
	}
	else if (event == moveLeft)
	{
		x = (window->player_x - 10) / 32;
		y = (window->player_y) / 32;
		if (window->map->map[y][x] != '1')
			window->player_x -= 10;
	}
	else if (event == viewRight)
	{
		window->pa += 0.5;
		if (window->pa > 2*PI)
			window->pa -= 2*PI;
	}
	else if (event == viewLeft)
	{
		window->pa -= 0.5;
		if (window->pa < 0)
			window->pa += 2*PI;
	}
	else if (event == escExit)
		return (close_window(window));
	printf("here--->%f \n", window->pa);
	return (0);
}

int	key_hook(int keycode, t_window *window)
{
	events event;
	int ret;

	event = get_event(keycode);
	ret = handle_event(event, window);
	draw_map(window);
	draw_the_rays3D(window);											// rays
	return (ret);
}
