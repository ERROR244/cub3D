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
	else if (keycode == 119)
		event = viewUp;
	else if (keycode == 115)
		event = viewDown;
	else if (keycode == 97)
		event = viewLeft;
	else if (keycode == 65307)
		event = escExit;
	return (event);
}

// int	p_in_the_map(char **map)
// {
// 	int	x;
// 	int	y;
//
// 	x = 0;
// 	y = 0;
// 	while (map[x])
// 	{
// 		y = 0;
// 		while (map[x][y])
// 		{
// 			if (map[x][y] == 'N')
// 				return (1);
// 			y++;
// 		}
// 		x++;
// 	}
// 	return (0);
// }

int handle_event(events event, t_window *window)
{
	if (event == moveForWard)
		window->player_y -= 10;
	else if (event == moveBackward)
		window->player_y += 10;
	else if (event == moveRight)
		window->player_x += 10;
	else if (event == moveLeft)
		window->player_x -= 10;
	if (event == escExit)
		return (close_window(window));
	return (0);
}

int	key_hook(int keycode, t_window *window)
{
	events event;
	int ret;

	event = get_event(keycode);
	ret = handle_event(event, window);
	return (ret);
}
