#include "../include/cub.h"

int plus = 1000;

bool haswallAt(long x, long y, t_window *window)
{
	int i;
	int j;
    int mapGridIndexX = round(x / window->TILE_SIZE);
    int mapGridIndexY = round(y / window->TILE_SIZE);

    if (x < 0 || x > window->i * window->TILE_SIZE || y < 0 || y > window->k *window->TILE_SIZE)
			return true;
	i = mapGridIndexY;
	j = 0;
	while (window->map->map[i][j] && j < mapGridIndexX)
		j++;
	if (j != mapGridIndexX)
		return (true);
    return (window->map->map[mapGridIndexY][mapGridIndexX] != '0' &&
			window->map->map[mapGridIndexY][mapGridIndexX] != 'N');
}

double normalizeAngle(double angle)
{
    angle = fmod(angle, (2 * PI));
    if (angle < 0)
        angle += 2 * PI;
    return (angle);
}

double	dis(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
}

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
        mlx_pixel_put(window->mlx, window->window, round(window->minimap*(X)), round(window->minimap*(Y)), 0xFF0000);
        X += Xinc;
        Y += Yinc;
    }
}

void cast_rays(t_window *window, int colid)
{
	bool Hwallhit;
	double Hwallx = 0;
	double Hwally = 0;

	Hwallhit = false;

	// find the closest (x, y)cordinate horizontal GRIND
	window->yfirststep = (int)(window->player_y / window->TILE_SIZE) * window->TILE_SIZE;
	if (window->ray[colid].is_ray_looking_down)
		window->yfirststep += window->TILE_SIZE;


	window->xfirststep = window->player_x + (window->yfirststep - window->player_y) / tan(window->ray[colid].ray_a);

	// xstep and ystep
	window->ystep = window->TILE_SIZE;
	if (window->ray[colid].is_ray_looking_up)
		window->ystep *= -1;

	window->xstep = window->TILE_SIZE / tan(window->ray[colid].ray_a);
	if (window->ray[colid].is_ray_looking_left && window->xstep > 0)
		window->xstep *= -1;
	if (window->ray[colid].is_ray_looking_right && window->xstep < 0)
		window->xstep *= -1;

	double nexthorztouchx = window->xfirststep;
	double nexthorztouchy = window->yfirststep;

	if (window->ray[colid].is_ray_looking_up)
		nexthorztouchy--;

	while (nexthorztouchx >= 0 && nexthorztouchy >= 0 &&
			nexthorztouchx < window->i * window->TILE_SIZE && nexthorztouchy < window->k * window->TILE_SIZE)
	{
		if (haswallAt(nexthorztouchx, nexthorztouchy, window))
		{
			Hwallhit = true;
			Hwallx = nexthorztouchx;
			Hwally = nexthorztouchy;
			break;
		}
		else
		{
			nexthorztouchx += window->xstep;
			nexthorztouchy += window->ystep;
		}
	}


	bool Vwallhit;
	double Vwallx = 0;
	double Vwally = 0;

	Vwallhit = false;

	// find the closest (x, y)cordinate vertical GRIND
	window->xfirststep = (int)(window->player_x / window->TILE_SIZE) * window->TILE_SIZE;
	if (window->ray[colid].is_ray_looking_right)
		window->xfirststep += window->TILE_SIZE;


	window->yfirststep = window->player_y + (window->xfirststep - window->player_x) * tan(window->ray[colid].ray_a);

	// xstep and ystep
	window->xstep = window->TILE_SIZE;
	if (window->ray[colid].is_ray_looking_left)
		window->xstep *= -1;

	window->ystep = window->TILE_SIZE * tan(window->ray[colid].ray_a);
	if (window->ray[colid].is_ray_looking_up && window->ystep > 0)
		window->ystep *= -1;
	if (window->ray[colid].is_ray_looking_down && window->ystep < 0)
		window->ystep *= -1;

	double nextvertouchx = window->xfirststep;
	double nextvertouchy = window->yfirststep;

	if (window->ray[colid].is_ray_looking_left)
		nextvertouchx--;

	// printf("%f %f \n", nextvertouchx, nextvertouchx / window->TILE_SIZE);
	// printf("%f %f \n", nextvertouchy, nextvertouchy / window->TILE_SIZE);
	// printf("%f %f \n", window->player_x, window->player_y);

	while (nextvertouchx >= 0 && nextvertouchy >= 0 &&
			nextvertouchx < window->i * window->TILE_SIZE && nextvertouchy < window->k * window->TILE_SIZE)
	{
		if (haswallAt(nextvertouchx, nextvertouchy, window))
		{
			Vwallhit = true;
			Vwallx = nextvertouchx;
			Vwally = nextvertouchy;
			break;
		}
		else
		{
			nextvertouchx += window->xstep;
			nextvertouchy += window->ystep;
		}
	}

	double hordis = DBL_MAX;
	double verdis = DBL_MAX;

	if (Hwallhit == true)
		hordis = dis(window->player_x, window->player_y, Hwallx, Hwally);
	if (Vwallhit == true)
		verdis = dis(window->player_x, window->player_y, Vwallx, Vwally);




	// window->ray[colid].ray_hit_x = window->player_x;
	// window->ray[colid].ray_hit_y = window->player_y;
	// window->ray[colid].distance = -1;
	if (verdis < hordis)
	{
		window->ray[colid].washitver = true;
		window->ray[colid].ray_hit_x = Vwallx;
		window->ray[colid].ray_hit_y = Vwally;
		window->ray[colid].distance = verdis;
	}
	else
	{
		window->ray[colid].washitver = false;
		window->ray[colid].ray_hit_x = Hwallx;
		window->ray[colid].ray_hit_y = Hwally;
		window->ray[colid].distance = hordis;
	}
	// printf("%f %f %f %f \n", window->ray[colid].ray_hit_x, window->ray[colid].ray_hit_y, window->player_x, window->player_y);
}

void draw_the_rays3D(t_window *window)
{
	int colid;

	colid = 0;
	window->ray_a = normalizeAngle(window->pa - to_rad(30));
	while (colid < window->rays)
	{
		window->ray[colid].ray_a = normalizeAngle(window->ray_a);
		window->ray[colid].col_id = colid;

		// //	create the player movment direction
		window->ray[colid].is_ray_looking_down = (window->ray[colid].ray_a > 0 && window->ray[colid].ray_a < PI);
		window->ray[colid].is_ray_looking_up = !window->ray[colid].is_ray_looking_down;
		window->ray[colid].is_ray_looking_right = (window->ray[colid].ray_a < 0.5*PI || window->ray[colid].ray_a > 1.5*PI);
		window->ray[colid].is_ray_looking_left = !window->ray[colid].is_ray_looking_right;

		// cast rays
		cast_rays(window, colid);

		//	render the rayr
		dda_for_line(	(window->player_x),
						(window->player_y),
						(window->ray[colid].ray_hit_x),
						(window->ray[colid].ray_hit_y),
						window
					);
		window->ray_a += to_rad(60) / window->rays;
		colid++;
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
			if (window->minimap*(j) < window->minimap*4.5 || window->minimap*(i) < window->minimap*4.5)
				ret = mlx_pixel_put(window->mlx, window->window, window->minimap*(x + i), window->minimap*(y + j), 0x808080);
			else
				ret = mlx_pixel_put(window->mlx, window->window, window->minimap*(x + i), window->minimap*(y + j), color);
			j++;
		}
		i++;
	}
	i = -4;
	while (i < 4 && ret == 0)
	{
		j = -4;
		while (j < 4 && ret == 0)
		{
			ret = mlx_pixel_put(window->mlx, window->window, window->minimap*(window->player_x + i), window->minimap*(window->player_y + j), 0x808080);
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
	return (ret);
}

void draw_2D_map(t_window *window)
{

	window->mlx = mlx_init();
	window->window_width = window->i * window->TILE_SIZE;
	window->window_hight = window->k * window->TILE_SIZE;
	window->window = mlx_new_window(window->mlx, window->window_width, window->window_hight, "cub3D");

	// draw_map(window);


	// mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 02, 1L<<0, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
}
