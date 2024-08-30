#include "../include/cub.h"

bool haswallAt(long x, long y, t_window *window)
{
	int j;
    int mapGridIndexX = floor(x / window->TILE_SIZE);
    int mapGridIndexY = floor(y / window->TILE_SIZE);

    if (x < 0 || x > window->i * window->TILE_SIZE || y < 0 || y > window->k *window->TILE_SIZE)
			return (true);
	j = 0;
	while (window->map->map[mapGridIndexY][j] && j < mapGridIndexX)
		j++;
	if (j != mapGridIndexX)
		return (true);
    return (window->map->map[mapGridIndexY][mapGridIndexX] != '0' &&
			window->map->map[mapGridIndexY][mapGridIndexX] != 'N');
}

double normalizeAngle(double angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0) {
        angle = TWO_PI + angle;
    }
    return angle;
}

double	dis(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void cast_rays(t_window *window, int colid)
{
    double hordis;
    double verdis;
	bool Hwallhit;
    bool Vwallhit;
	double Hwallx;
	double Hwally;
    double Vwallx;
    double Vwally;
    double nexthorztouchx;
	double nexthorztouchy;
    double nextvertouchx;
    double nextvertouchy;



	Hwallhit = false;
    Vwallhit = false;
    hordis = DBL_MAX;
    verdis = DBL_MAX;

	// find the closest (x, y)cordinate horizontal GRIND
	window->yfirststep = floor(window->player_y / window->TILE_SIZE) * window->TILE_SIZE;
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

	nexthorztouchx = window->xfirststep;
	nexthorztouchy = window->yfirststep;

	if (window->ray[colid].is_ray_looking_up)
		nexthorztouchy--;

	while (nexthorztouchx >= 0 && nexthorztouchy >= 0 &&
			nexthorztouchx < window->i * window->TILE_SIZE && nexthorztouchy < window->k * window->TILE_SIZE)
	{
		if (haswallAt(nexthorztouchx, nexthorztouchy, window))
		{
            if (window->ray[colid].is_ray_looking_up)
            	nexthorztouchy++;
			Hwallhit = true;
			Hwallx = nexthorztouchx;
			Hwally = nexthorztouchy;
			break ;
		}
		else
		{
			nexthorztouchx += window->xstep;
			nexthorztouchy += window->ystep;
		}
	}




	// find the closest (x, y)cordinate vertical GRIND
	window->xfirststep = floor(window->player_x / window->TILE_SIZE) * window->TILE_SIZE;
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

    nextvertouchx = window->xfirststep;
    nextvertouchy = window->yfirststep;


	if (window->ray[colid].is_ray_looking_left)
		nextvertouchx--;

	while (nextvertouchx >= 0 && nextvertouchy >= 0 &&
			nextvertouchx < window->i * window->TILE_SIZE && nextvertouchy < window->k * window->TILE_SIZE)
	{
		if (haswallAt(nextvertouchx, nextvertouchy, window))
		{
            if (window->ray[colid].is_ray_looking_left)
        	{
                nextvertouchx++;
            }
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

	if (Hwallhit == true)
		hordis = dis(window->player_x, window->player_y, Hwallx, Hwally);
	if (Vwallhit == true)
		verdis = dis(window->player_x, window->player_y, Vwallx, Vwally);
	if (hordis < verdis)
	{
		window->ray[colid].washitver = false;
		window->ray[colid].ray_hit_x = Hwallx;
		window->ray[colid].ray_hit_y = Hwally;
		window->ray[colid].distance = hordis;
	}
	else
	{
		window->ray[colid].washitver = true;
		window->ray[colid].ray_hit_x = Vwallx;
		window->ray[colid].ray_hit_y = Vwally;
		window->ray[colid].distance = verdis;
	}
}

void rays3D_cast(t_window *window)
{
	int colid;

	colid = 0;
	window->ray_a = normalizeAngle(window->pa - (FOV_ANGLE / 2));
	while (colid < window->rays)
	{
		window->ray[colid].ray_a = normalizeAngle(window->ray_a);
		window->ray[colid].col_id = colid;
		window->ray[colid].is_ray_looking_down = (window->ray[colid].ray_a > 0 && window->ray[colid].ray_a < PI);
		window->ray[colid].is_ray_looking_up = !window->ray[colid].is_ray_looking_down;
		window->ray[colid].is_ray_looking_right = (window->ray[colid].ray_a < 0.5*PI || window->ray[colid].ray_a > 1.5*PI);
		window->ray[colid].is_ray_looking_left = !window->ray[colid].is_ray_looking_right;
		cast_rays(window, colid);
		//	render the rayr
		// dda_for_line(	(window->player_x),
		// 				(window->player_y),
		// 				(window->ray[colid].ray_hit_x),
		// 				(window->ray[colid].ray_hit_y),
		// 				window
		// 			);
		window->ray_a += FOV_ANGLE / window->rays;
		colid++;
	}
}
