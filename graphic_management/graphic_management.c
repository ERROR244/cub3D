#include "../include/cub.h"

char *eventstr[] = {
	"moveForWard", "moveBackward", "moveRight", "moveLeft",
	"viewUp", "viewDown", "viewRight", "viewLeft",
	"escExit", "none"
};

int	close_window(t_window *window)
{
	printf("Good game\n");
    exit_game(window);
	mlx_destroy_window(window->mlx, window->window);
	exit(EXIT_SUCCESS);
	return (0);
}

int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

void DDA(int X0, int Y0, int X1, int Y1, t_window *window)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;

	int steps = 20;
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;

	float X = X0;
	float Y = Y0;
	for (int i = 0; i <= 100; i++) {
		mlx_pixel_put(window->mlx, window->window, round(X), round(Y), 0x808080);
		Y -= Yinc;
		X -= Xinc;
		// X += Xinc;
	}
}

int draw_squar(t_window *window, int y, int x, int color)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = 0;
	while (i < 64 && ret == 0)
	{
		j = 0;
		while (j < 64 && ret == 0)
		{
			if (j < 2 || i < 2)
				ret = mlx_pixel_put(window->mlx, window->window, x + i, y + j, 0x808080);
			else
				ret = mlx_pixel_put(window->mlx, window->window, x + i, y + j, color);
			j++;
		}
		i++;
	}
	i = 0;
	DDA(window->player_x + 5, window->player_y + 5, window->player_x + 10, window->player_y + 10, window);
	while (i < 10 && ret == 0)
	{
		j = 0;
		while (j < 10 && ret == 0)
		{
			ret = mlx_pixel_put(window->mlx, window->window, window->player_x + i, window->player_y + j, 0x808080);
			j++;
		}
		i++;
	}
	return (ret);
}

int draw_map(t_window *window)
{
	char **map;
	int i;
	int j;
	int x = 0;
	int y = 0;
	int ret;

	i = 0;
	ret = 0;
	map = window->map->map;
	while (map[i] && ret == 0)
	{
		j = 0;
		y = 0;
		while (map[i][j] && ret == 0)
		{
			if (map[i][j] == '0')
				ret = draw_squar(window, x, y, 0xFFFFFF);
			else if (map[i][j] == '1' || map[i][j] == ' ')
				ret = draw_squar(window, x, y, 0x000000);
			else if (map[i][j] == 'N')
				ret = draw_squar(window, x, y, 0xFFFFFF);
			j++;
			y += 64;
		}
		x += 64;
		i++;
	}
	return (ret);
}


void	graphic_management(t_window *window)
{
	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->i * 64, window->k * 64, "cub3D");

	mlx_loop_hook(window->mlx, draw_map, window);

	mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
}
