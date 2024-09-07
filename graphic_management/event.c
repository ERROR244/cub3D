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
	else if (keycode == 32)
		event = OpenClose;
	return (event);
}

int get_tmpx_tmpy(char c, t_window *window, events event)
{
	int		tmp;

	if (c == 'x')
		tmp = -5;
	else
		tmp = 10;
	if (c == 'x'
		&& ((window->ray[window->rays/2].is_ray_looking_right && event == moveForWard)
		|| (window->ray[window->rays/2].is_ray_looking_left && event == moveBackward)))
		tmp = 10;
	if (c == 'y'
		&& ((window->ray[window->rays/2].is_ray_looking_up && event == moveForWard)
		|| (window->ray[window->rays/2].is_ray_looking_down && event == moveBackward)))
		tmp = -5;
	return (tmp);
}

int handle_event1(events event, t_window *window, int x, int y)
{
	int 	dir;
	int		tmpx;
	int		tmpy;

	if (event == moveForWard)
		dir = 1;
	else
		dir = -1;
	x = (window->player_x + (cos(window->pa) * 3 * dir));
	y = (window->player_y + (sin(window->pa) * 3 * dir));
	tmpx = get_tmpx_tmpy('x', window, event);
	tmpy = get_tmpx_tmpy('y', window, event);
	window->update_waidow = true;
	if (!haswallAt(x+tmpx, window->player_y+tmpy, window) && dir != 0)
		window->player_x = x;
	if (!haswallAt(window->player_x+tmpx, y+tmpy, window) && dir != 0)
		window->player_y = y;
	if (window->player_x != x && window->player_y != y)
		window->update_waidow = false;
	return (0);
}

void open_close_d(char *c)
{
	if (*c == 'D')
	*c = 'A';
	else
	*c = 'D';
}

int handle_event0(events event, t_window *window)
{
	int i;
	int j;

	if (event == OpenClose)
	{
		window->update_waidow = true;
		j = (int)(window->player_x / window->TILE_SIZE);
		i = (int)(window->player_y / window->TILE_SIZE);
		if (window->map->map[i+1][j] && (window->map->map[i+1][j] == 'D' || window->map->map[i+1][j] == 'A'))
			open_close_d(&window->map->map[i+1][j]);
		else if (window->map->map[i][j+1] && (window->map->map[i][j+1] == 'D' || window->map->map[i][j+1] == 'A'))
			open_close_d(&window->map->map[i][j+1]);
		else if (i - 1 >= 0 && (window->map->map[i-1][j] == 'D' || window->map->map[i-1][j] == 'A'))
			open_close_d(&window->map->map[i-1][j]);
		else if (j - 1 >= 0 && (window->map->map[i][j-1] == 'D' || window->map->map[i][j-1] == 'A'))
			open_close_d(&window->map->map[i][j-1]);
		else
			window->update_waidow = false;
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

int handle_mouse(t_window *window)
{
	int x = 0;
	int y = 0;

	mlx_mouse_get_pos(window->mlx, window->window, &x, &y);
	int diff = window->mouse_x - x;
	mlx_mouse_get_pos(window->mlx, window->window, &window->mouse_x, &window->mouse_y);
		window->update_waidow_for_mouse = true;
		if (diff > 0)
			window->pa += diff * 0.005;
		else if (diff < 0)
			window->pa += diff * 0.005;
		else
			window->update_waidow_for_mouse = false;
		if (window->pa < 0)
			window->pa += 2*PI;
		else if (window->pa > 2*PI)
			window->pa -= 2*PI;
	return (0);
}


int	key_hook(int keycode, t_window *window)
{
	events event;

	event = get_event(keycode);
	handle_event0(event, window);
	if (event == moveForWard || event == moveBackward)
		handle_event1(event, window, 0, 0);
	handle_event2(event, window);
	// handle_mouse(window);
	return (0);
}
