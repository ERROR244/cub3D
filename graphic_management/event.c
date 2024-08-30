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
	else if (event == moveLeft)
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
		return (close_window(window));
	return (0);
}

int draw_rect(void *mlx, void *window, int x, int y, int width, int height, int color)
{
	int ret;
    int i;
    int j;

	i = 0;
	ret = 0;
    while (i < width && ret == 0)
    {
		j = 0;
        while (j < height && ret == 0)
        {
            ret = mlx_pixel_put(mlx, window, (x + i), (y + j), color);
			j++;
		}
		i++;
    }
	return (ret);
}

int render3d(t_window *window)
{
	int ret;
	int i;
	double displane;
	double distance;
	double wall3dhight;

	i = 0;
	ret = 0;
	while (i < window->rays && ret == 0)
	{
		distance = window->ray[i].distance * cos(window->ray[i].ray_a - window->pa);
		displane = (window->window_width / 2) / tan(to_rad(60) / 2);
		wall3dhight = (window->TILE_SIZE / distance) * displane;
		// printf("%d %f %f %f\n", i, window->ray[i].distance, wall3dhight, displane);

		draw_rect(window->mlx,
				  window->window,
				  round(i * window->wall_wigth),
				  round((window->window_hight / 2) - (wall3dhight / 2)),
				  round(window->wall_wigth),
				  round(wall3dhight),
				  0xFFFFFF
				  );
		i++;
	}
	return (ret);
}

int	key_hook(int keycode, t_window *window)
{
	events event;
	int ret;

	mlx_clear_window(window->mlx, window->window);
	event = get_event(keycode);
	ret = handle_event(event, window);
	render3d(window);
	draw_map(window);
	draw_the_rays3D(window);											// rays
	return (ret);
}
