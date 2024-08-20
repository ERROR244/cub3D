#include "../include/cub.h"

char *eventstr[] = {
	"moveForWard", "moveBackward", "moveRight", "moveLeft",
	"viewUp", "viewDown", "viewRight", "viewLeft",
	"escExit", "none"
};

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

int	p_in_the_map(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'N')
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

int move(t_window *window, int i, int j)
{
	char	**map;
	int		x;
	int		y;

	x = window->player_x;
	y = window->player_y;
	map = window->map->map;
	if (map[x][y] && map[x + i][y + j] == '0')
	{
		map[x][y] = '0';
		if (p_in_the_map(map) == 0)
		{
			map[x + i][y + j] = 'N';
			window->player_x = x + i;
			window->player_y = y + j;
		}
	}
	return (0);
}

int handle_event(events event, t_window *window)
{
	int ret;

	ret = 0;
	if (event == moveForWard)
		ret = move(window, -1, 0);
	else if (event == moveBackward)
		ret = move(window, 1, 0);
	else if (event == moveRight)
		ret = move(window, 0, 1);
	else if (event == moveLeft)
		ret = move(window, 0, -1);
	else if (event == escExit)
		ret = close_window(window);
	return (ret);
}

int	key_hook(int keycode, t_window *window)
{
	events event;
	int ret;

	event = get_event(keycode);
	ret = handle_event(event, window);
	// print_array(window->map->map);
	return (ret);
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
	window->window = mlx_new_window(window->mlx, 140, 90, "cub3D");





	mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
}
