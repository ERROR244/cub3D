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

void handle_ver(t_window *window, int x, int y)
{
	int tmp;
	double diff;

	window->update_waidow = true;
	tmp = 10;
	if (window->ray[window->rays/2].is_ray_looking_up)
		diff = window->pa - 3*PI/2;
	else
	{
		tmp *= -1;
		diff = -1 * (window->pa - PI/2);
	}
	if (diff < 0 && !haswallAt(x+(diff * 1.5), y+tmp, window))
		window->player_x += (diff * 1.5);
	else if (diff > 0 && !haswallAt(x+(diff * 1.5), y+tmp, window))
		window->player_x += (diff * 1.5);
	else
		window->update_waidow = false;
}

void handle_hor(t_window *window, int x, int y)
{
	int tmp;
	double diff;

	window->update_waidow = true;
	tmp = -10;
	if (window->ray[window->rays/2].is_ray_looking_right)
		diff = (window->pa > 5) ? window->pa - TWO_PI : window->pa;
	else
	{
		tmp *= -1;
		diff = -1 * (window->pa - PI);
	}
	if (diff < 0 && !haswallAt(x+tmp, y+(diff * 1.5), window))
		window->player_y += (diff * 1.5);
	else if (diff > 0 && !haswallAt(x+tmp, y+(diff * 1.5), window))
		window->player_y += (diff * 1.5);
	else
		window->update_waidow = false;
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

int handle_event1(events event, t_window *window, int x, int y)
{
	int 	dir;

	dir = 0;
	if (event == moveForWard)
		dir = 1;
	else if (event == moveBackward)
		dir = -1;
	x = (window->player_x + (cos(window->pa) * 3 * dir));
	y = (window->player_y + (sin(window->pa) * 3 * dir));
	if (!haswallAt(x, y, window) && dir != 0)
	{
		window->update_waidow = true;
		window->player_y = y;
		window->player_x = x;
	}
	else if (dir != 0 && window->ray[window->rays/2].washitver == false)
		handle_ver(window, x, y);
	else if (dir != 0 && window->ray[window->rays/2].washitver == true)
		handle_hor(window, x, y);
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
	// if (x > 0 && x < window->window_width && y > 0 && y < window->window_hight)
	// {
		window->update_waidow_for_mouse = true;
		if (diff > 0)
			window->pa += diff * 0.005;
		else if (diff < 0)
			window->pa += diff * 0.005;
		else
			window->update_waidow_for_mouse = false;
	// }
	return (0);
}


int	key_hook(int keycode, t_window *window)
{
	events event;

	event = get_event(keycode);
	handle_event0(event, window);
	handle_event1(event, window, 0, 0);
	handle_event2(event, window);
	// handle_mouse(window);
	return (0);
}
