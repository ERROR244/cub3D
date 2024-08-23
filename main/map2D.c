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

double fabs(double n) { return ((n > 0) ? n : (n * (-1))); } ;

void draw_line_dda(t_window *window, int x0, int y0)
{
    double steps = fabs(window->pdx) > fabs(window->pdy) ? fabs(window->pdx) : fabs(window->pdy);

    double x_inc = window->pdx / (double)steps;
    double y_inc = window->pdy / (double)steps;

    double x = x0 + 3;
    double y = y0 + 3;

    for (int i = 0; i <= 20; i++)
	{
        mlx_pixel_put(window->mlx, window->window, round(x), round(y), 0xFF0000);
        x += x_inc;
        y += y_inc;
    }
}

void draw_the_rays3D(t_window *window)
{
	(void)window;
}

int draw_squar(t_window *window, int y, int x, int color)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = 0;
	while (i < 32 && ret == 0)
	{
		j = 0;
		while (j < 32 && ret == 0)
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
	while (i < 8 && ret == 0)
	{
		j = 0;
		while (j < 8 && ret == 0)
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
	draw_the_rays3D(window);
	draw_line_dda(window, window->player_x, window->player_y);
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
			if (map[i][j + 1] == '\0')
			{
				while (j < window->i)
				{
					ret = draw_squar(window, x, y, 0x000000);
					y += 32;
					j++;
				}
				break ;
			}
			j++;
			y += 32;
		}
		x += 32;
		i++;
	}
	return (ret);
}

void draw_2D_map(t_window *window)
{

	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->i * 32, window->k * 32, "cub3D");

	window->pdx = cos(window->pa) * 5;
	window->pdy = sin(window->pa) * 5;

	// window->dirX = -1;
	// window->dirY = 0;
	// window->planeX = 0;
	// window->planeY = 0.66;

	mlx_loop_hook(window->mlx, draw_map, window);

	mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
}
