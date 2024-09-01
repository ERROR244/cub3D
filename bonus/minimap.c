#include "../include/cub.h"

int draw_mini_squar(t_window *window, double y, double x, int color, int size)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = 0;
	while (i < size && ret == 0)
	{
		j = 0;
		while (j < size && ret == 0)
		{
			ret = my_mlx_pixel_put(window, x + i, y + j, color);
			j++;
		}
		i++;
	}
	return (ret);
}

int ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int draw_mini_map(t_window *window)
{
	char **map;
	double playerx = (double)(window->player_x / 64);
	double playery = (double)(window->player_y / 64);
	int i;
	int j;
	int x = 0;
	int y = 0;
	int ret;
	int xx, yy;
	int x_start;
	int y_start;
	int x_end;
	int y_end;

	xx = (int)(playerx) - MINI_MAP_SIZE;
	yy = (int)(playery) - MINI_MAP_SIZE;
	if (xx < 0)
	{
		x_start = 0;
		x_end = (int)(playerx) + MINI_MAP_SIZE - xx;
	}
	else
	{
		x_end = (int)(playerx) + MINI_MAP_SIZE;
		x_start = (int)(playerx) - MINI_MAP_SIZE;
	}
	if (yy < 0)
	{
		y_start = 0;
		y_end = (int)(playery) + MINI_MAP_SIZE - yy;
	}
	else
	{
		y_end = (int)(playery) + MINI_MAP_SIZE;
		y_start = (int)(playery) - MINI_MAP_SIZE;
	}

	if (xx < 0)
		xx = 0;
	if (yy < 0)
		yy = 0;
	playerx -= xx;
	playery -= yy;
	ret = 0;
	map = window->map->map;
	i = y_start;
	while (map[i] &&  i < y_end && ret == 0)
	{
		j = x_start;
		y = 0;
		while (map[i][j] && j < x_end && ret == 0)
		{
			if (map[i][j] == '0' || map[i][j] == 'N')
				ret = draw_mini_squar(window, x, y, 0x0000FF, 16);
			else if (map[i][j] == '1' || map[i][j] == ' ' || map[i][j] == '\0' )
				ret = draw_mini_squar(window, x, y, 0x00FFFF, 16);
			j++;
			if (map[i][j] == '\0' || map[i][j] == '\n')
			{
				while (j <= (window->i + 4) && j <= x_end)
				{
					ret = draw_mini_squar(window, x, y, 0x00FFFF, 16);
					y += 16;
					j++;
				}
				break;
			}
			y += 16;
		}
		x += 16;
		i++;
	}
	int k = 0;
	int l = 0;
	if (i < y_end)
	{
		while (i + k < y_end)
		{
			l = 0;
			y = 0;
			while (l < (MINI_MAP_SIZE * 2))
			{
				ret = draw_mini_squar(window, x, y, 0x00FFFF, 16);
				 y += 16;
				l++;
			}
			x += 16;
			k++;
		}
	}
	ret = draw_mini_squar(window, (playery * 16), (playerx * 16), 0x00000, 6);

    // for (int i = 0; i < window->rays; i++)
    // {
    //     dda_for_line(	(playerx*16),
	// 					(playery*16),
	// 					(window->ray[i].ray_hit_x / 64)*16,
	// 					(window->ray[i].ray_hit_y / 64)*16,
	// 					window
	// 				);
    // }
	return (ret);
}
