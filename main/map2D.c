#include "../include/cub.h"


double fabs(double n) { return ((n > 0) ? n : (n * (-1))); } ;

void dda_for_line(double X0, double Y0, double X1, double Y1, t_window *window)
{
    double dx = X1 - X0;
    double dy = Y1 - Y0;

    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;

    double X = X0;
    double Y = Y0;
    for (int i = 0; i <= steps; i++)
	{
        mlx_pixel_put(window->mlx, window->window, floor(window->minimap*(X)), floor(window->minimap*(Y)), 0xFF0000);
        X += Xinc;
        Y += Yinc;
    }
}


int draw_squar(t_window *window, int y, int x, int color)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = 0;
	while (i < window->TILE_SIZE && ret == 0)
	{
		j = 0;
		while (j < window->TILE_SIZE && ret == 0)
		{
			// if (window->minimap*(j) < window->minimap*4.5 || window->minimap*(i) < window->minimap*4.5)
			// 	ret = mlx_pixel_put(window->mlx, window->window, window->minimap*(x + i), window->minimap*(y + j), 0x808080);
			// else
				ret = mlx_pixel_put(window->mlx, window->window, window->minimap*(x + i), window->minimap*(y + j), color);
			j++;
		}
		i++;
	}
	i = -6;
	while (i < 6 && ret == 0)
	{
		j = -6;
		while (j < 6 && ret == 0)
		{
			ret = mlx_pixel_put(window->mlx, window->window, window->minimap*(window->player_x + i), window->minimap*(window->player_y + j), 0x000000);
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
				ret = draw_squar(window, x, y, 0x0000FF);
			else if (map[i][j] == 'N')
				ret = draw_squar(window, x, y, 0xFFFFFF);
			if (map[i][j + 1] == '\0')
			{
				while (j <= window->i)
				{
					ret = draw_squar(window, x, y, 0x000000);
					y += window->TILE_SIZE;
					j++;
				}
				break ;
			}
			j++;
			y += window->TILE_SIZE;
		}
		x += window->TILE_SIZE;
		i++;
	}
    dda_for_line(	window->player_x,
					window->player_y,
					window->player_x + cos(window->pa) * 30,
					window->player_y + sin(window->pa) * 30,
					window
				);			// direction
	return (ret);
}

// void draw_2D_map(t_window *window)
// {
//
// 	window->mlx = mlx_init();
// 	window->window = mlx_new_window(window->mlx, window->window_width, window->window_hight, "cub3D");
//
// 	// draw_map(window);
//
//
// 	mlx_key_hook(window->window, key_hook, window);
// 	// mlx_hook(window->window, 02, 1L<<0, key_hook, window);
// 	mlx_hook(window->window, 17, 0L, close_window, window);
//     mlx_loop(window->mlx);
// }
