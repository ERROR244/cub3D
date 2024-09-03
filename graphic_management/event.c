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
	if (keycode == 65362 || keycode == 119)
		event = moveForWard;
	else if (keycode == 65364 || keycode == 115)
		event = moveBackward;
	else if (keycode == 65363 || keycode == 100)
		event = viewRight;
	else if (keycode == 65361 || keycode == 97)
		event = viewLeft;
	else if (keycode == 65307)
		event = escExit;
	return (event);
}

int handle_event1(events event, t_window *window, int x, int y)
{
	int dir;

	dir = 0;
	if (event == moveForWard)
		dir = 1;
	else if (event == moveBackward)
		dir = -1;
	x = (window->player_x + (cos(window->pa) * 6 * dir));
	y = (window->player_y + (sin(window->pa) * 6 * dir));
	if (!haswallAt(x, y, window) && dir != 0)
	{
		window->update_waidow = true;
		window->player_y = y;
		window->player_x = x;
	}
	return (0);
}

int handle_event2(events event, t_window *window)
{
	if (event == viewRight)
	{
		window->update_waidow = true;
		window->pa += 0.1;
		if (window->pa > 2*PI)
			window->pa -= 2*PI;
	}
	else if (event == viewLeft)
	{
		window->update_waidow = true;
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

	ret = 0;
	// mlx_clear_window(window->mlx, window->window);
	event = get_event(keycode);
	handle_event1(event, window, 0, 0);
	handle_event2(event, window);
	// draw_map(window);
	// rays3D_cast(window);
	// ret = render3d(window);
	// draw_mini_map(window);
	// windoww->img->img = window->img->tmp_img;
	// if (window->update_waidow == true)
	// 	mlx_put_image_to_window(window->mlx, window->window, window->img->img, 0, 0);
	// window->update_waidow = false;
	return (ret);
}
