#include "../include/cub.h"

int plus = 1000;

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

void dda_for_line(int X0, int Y0, int X1, int Y1, t_window *window) 
{ 
    double dx = X1 - X0; 
    double dy = Y1 - Y0; 
  
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy); 
  
    double Xinc = dx / (double)steps; 
    double Yinc = dy / (double)steps; 
  
    double X = X0; 
    double Y = Y0; 
    for (int i = 0; i <= steps + plus && window->map->map[(int)Y/32][(int)X/32] != '1'; i++)
	{
        mlx_pixel_put(window->mlx, window->window, round(X), round(Y), 0xFF0000);
        X += Xinc;
        Y += Yinc;
    } 
}

void cast_rays(t_window *window)
{
	/////////////////////////////////////////
	// horizontal RAY-GRIND intersection code
	/////////////////////////////////////////

	// find the closest (x, y)cordinate horizontal GRIND
	window->yfirststep = round(window->player_y / 32) * 32;
	window->xfirststep = window->player_x-(window->yfirststep-window->player_y)/tan(window->ray_a);

}

void draw_the_rays3D(t_window *window)
{
	int colid;
	int i;

	i = 0;
	colid = 0;
	window->ray_a = window->pa - to_rad(30);
	// while (i < 1)
	while (i < window->rays)
	{
		window->ray[colid].ray_a = window->ray_a;
		window->ray[colid].col_id = colid;

		// up and down
		window->ray[colid].is_ray_looking_down = (window->ray[colid].ray_a > 0 && (window->ray[colid].ray_a < PI || window->ray[colid].ray_a > 2*PI));
		window->ray[colid].is_ray_looking_up = !window->ray[colid].is_ray_looking_down;

		// left and right
		window->ray[colid].is_ray_looking_right = (window->ray[colid].ray_a > 3*PI/2 || window->ray[colid].ray_a < PI/2);
		window->ray[colid].is_ray_looking_left = !window->ray[colid].is_ray_looking_right;

		if (window->ray[colid].is_ray_looking_down == true && window->ray[colid].is_ray_looking_right == true)
			printf("%f -- right down\n", window->ray[colid].ray_a);
		else if (window->ray[colid].is_ray_looking_down == false && window->ray[colid].is_ray_looking_right == true)
			printf("%f -- right up\n", window->ray[colid].ray_a);
		else if (window->ray[colid].is_ray_looking_down == false && window->ray[colid].is_ray_looking_right == false)
			printf("%f -- left up\n", window->ray[colid].ray_a);
		else if (window->ray[colid].is_ray_looking_down == true && window->ray[colid].is_ray_looking_right == false)
			printf("%f -- left down\n", window->ray[colid].ray_a);

		// cast rays
		cast_rays(window);		

		//	render the rayr
		if (i == 0 || i == window->rays - 1)
			dda_for_line(	window->player_x,
							window->player_y,
							window->player_x + cos(window->ray_a) * 30,
							window->player_y + sin(window->ray_a) * 30,
							window
						);
		window->ray_a += to_rad(60) / window->rays;
		colid++;
		i++;
	}
	printf("-----------------------------------------------------------------------\n");
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
	i = -4;
	while (i < 4 && ret == 0)
	{
		j = -4;
		while (j < 4 && ret == 0)
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
			if (map[i][j + 1] == '\0')
			{
				while (j <= window->i)
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
	draw_the_rays3D(window);											// rays
	dda_for_line(	window->player_x,
					window->player_y,
					window->player_x + cos(window->pa) * 30,
					window->player_y + sin(window->pa) * 30,
					window
				);			// direction
	return (ret);
}

void draw_2D_map(t_window *window)
{

	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->i * 32, window->k * 32, "cub3D");

	// window->dirX = -1;
	// window->dirY = 0;
	// window->planeX = 0;
	// window->planeY = 0.66;

	
	mlx_key_hook(window->window, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
}
