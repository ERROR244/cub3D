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

int handle_event1(events event, t_window *window, int x, int y)
{
	int dir;

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

int handle_event0(events event, t_window *window)
{
	int i;
	int j;

	if (event == OpenClose)
	{
		j = (int)(window->player_x / window->TILE_SIZE);
		i = (int)(window->player_y / window->TILE_SIZE);
		window->update_waidow = true;
		// printf("%d %d \n", x, y);
		// printf("window: %p, map: %p, map->map: %p\n", (void*)window, (void*)window->map, (void*)window->map->map);
		// char **map = window->map->map;
		if (window->map->map[i+1][j] && (window->map->map[i+1][j] == 'D' || window->map->map[i+1][j] == 'A'))
		{
			if (window->map->map[i+1][j] == 'D')
				window->map->map[i+1][j] = 'A';
			else
				window->map->map[i+1][j] = 'D';
		}
		else if (window->map->map[i][j+1] && (window->map->map[i][j+1] == 'D' || window->map->map[i][j+1] == 'A'))
		{
			if (window->map->map[i][j+1] == 'D')
				window->map->map[i][j+1] = 'A';
			else
				window->map->map[i][j+1] = 'D';
		}
		else if (i - 1 >= 0 && (window->map->map[i-1][j] == 'D' || window->map->map[i-1][j] == 'A'))
		{
			if (window->map->map[i-1][j] == 'D')
				window->map->map[i-1][j] = 'A';
			else
				window->map->map[i-1][j] = 'D';
		}
		else if (j - 1 >= 0 && (window->map->map[i][j-1] == 'D' || window->map->map[i][j-1] == 'A'))
		{
			if (window->map->map[i][j-1] == 'D')
				window->map->map[i][j-1] = 'A';
			else
				window->map->map[i][j-1] = 'D';
		}
		else
			window->update_waidow = true;
		// print_array(window->map->map);
	}
	return (0);
}

int fft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int handle_mouse(t_window *window)
{
	int x = 0;
	int y = 0;
	mlx_mouse_get_pos(window->mlx, window->window, &x, &y);
	int hold = x - window->mouse_x;
	mlx_mouse_get_pos(window->mlx, window->window, &window->mouse_x, &window->mouse_y);
	if (hold > 0)
	{
		window->update_waidow = true;
		window->pa += fft_abs(hold * 4) * 0.002;
		if (window->pa > 2*PI)
			window->pa -= 2*PI;
	}
	else if (hold < 0)
	{
		window->update_waidow = true;
		window->pa -= fft_abs(hold * 4) * 0.002;
		if (window->pa < 0)
			window->pa += 2*PI;
	}
	return (0);
}


int	key_hook(int keycode, t_window *window)
{
	events event;
	int ret;

	ret = 0;
	// printf("%d\n", keycode);
	// mlx_clear_window(window->mlx, window->window);
	event = get_event(keycode);
	handle_event0(event, window);
	handle_event1(event, window, 0, 0);
	handle_event2(event, window);
	handle_mouse(window);
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

// int	kkey_hook(int keycode, t_window *window)
// {
// 	events event;
// 	int ret;
//
// 	ret = 0;
// 	// printf("%d\n", keycode);
// 	// mlx_clear_window(window->mlx, window->window);
// 	event = get_event(keycode);
// 	// handle_event0(event, window);
// 	// handle_event1(event, window, 0, 0);
// 	// handle_event2(event, window);
// 	// handle_mouse(window);
// 	// draw_map(window);
// 	// rays3D_cast(window);
// 	// ret = render3d(window);
// 	// draw_mini_map(window);
// 	// windoww->img->img = window->img->tmp_img;
// 	// if (window->update_waidow == true)
// 	// 	mlx_put_image_to_window(window->mlx, window->window, window->img->img, 0, 0);
// 	// window->update_waidow = false;
// 	return (ret);
// }
