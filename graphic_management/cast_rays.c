#include "../include/cub.h"

bool haswallAt(long x, long y, t_window *window)
{
	int j;
    int mapGridIndexX = (int)(x / window->TILE_SIZE);
    int mapGridIndexY = (int)(y / window->TILE_SIZE);

    if (x < 0 || x > window->i * window->TILE_SIZE || y < 0 || y > window->k *window->TILE_SIZE)
			return (true);
	j = 0;
	while (window->map->map[mapGridIndexY][j] && j < mapGridIndexX)
		j++;
	if (j != mapGridIndexX)
		return (true);
    return (window->map->map[mapGridIndexY][mapGridIndexX] != '0' &&
			window->map->map[mapGridIndexY][mapGridIndexX] != 'P' &&
			window->map->map[mapGridIndexY][mapGridIndexX] != 'A');
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

t_cast find_h_xy_setp(t_window *window, int col_id, t_cast cast)
{
	window->yfirststep = floor(window->player_y / window->TILE_SIZE) * window->TILE_SIZE;
	if (window->ray[col_id].is_ray_looking_down)
		window->yfirststep += window->TILE_SIZE;
	window->xfirststep = window->player_x + (window->yfirststep - window->player_y) / tan(window->ray[col_id].ray_a);
	window->ystep = window->TILE_SIZE;
	if (window->ray[col_id].is_ray_looking_up)
		window->ystep *= -1;
	window->xstep = window->TILE_SIZE / tan(window->ray[col_id].ray_a);
	if (window->ray[col_id].is_ray_looking_left && window->xstep > 0)
		window->xstep *= -1;
	if (window->ray[col_id].is_ray_looking_right && window->xstep < 0)
		window->xstep *= -1;
	cast.nexthorztouchx = window->xfirststep;
	cast.nexthorztouchy = window->yfirststep;
	if (window->ray[col_id].is_ray_looking_up)
		cast.nexthorztouchy--;
	return (cast);
}

t_cast find_v_xy_setp(t_window *window, int col_id, t_cast cast)
{
	window->xfirststep = floor(window->player_x / window->TILE_SIZE) * window->TILE_SIZE;
	if (window->ray[col_id].is_ray_looking_right)
		window->xfirststep += window->TILE_SIZE;
	window->yfirststep = window->player_y + (window->xfirststep - window->player_x) * tan(window->ray[col_id].ray_a);
	window->xstep = window->TILE_SIZE;
	if (window->ray[col_id].is_ray_looking_left)
		window->xstep *= -1;
	window->ystep = window->TILE_SIZE * tan(window->ray[col_id].ray_a);
	if (window->ray[col_id].is_ray_looking_up && window->ystep > 0)
		window->ystep *= -1;
	if (window->ray[col_id].is_ray_looking_down && window->ystep < 0)
		window->ystep *= -1;
    cast.nextvertouchx = window->xfirststep;
    cast.nextvertouchy = window->yfirststep;
	if (window->ray[col_id].is_ray_looking_left)
		cast.nextvertouchx--;
	return (cast);
}

t_cast find_h_xy_wall_hit(t_window *window, int col_id, t_cast cast)
{
	while (cast.nexthorztouchx >= 0 && cast.nexthorztouchy >= 0
			&& cast.nexthorztouchx < window->i * window->TILE_SIZE
			&& cast.nexthorztouchy < window->k * window->TILE_SIZE)
	{
		if (haswallAt(cast.nexthorztouchx, cast.nexthorztouchy, window))
		{
            if (window->ray[col_id].is_ray_looking_up)
            	cast.nexthorztouchy++;
			cast.Hwallhit = true;
			cast.Hwallx = cast.nexthorztouchx;
			cast.Hwally = cast.nexthorztouchy;
			break ;
		}
		else
		{
			cast.nexthorztouchx += window->xstep;
			cast.nexthorztouchy += window->ystep;
		}
	}
	return (cast);
}

t_cast find_v_xy_wall_hit(t_window *window, int col_id, t_cast cast)
{
	while (cast.nextvertouchx >= 0 && cast.nextvertouchy >= 0
			&& cast.nextvertouchx < window->i * window->TILE_SIZE
			&& cast.nextvertouchy < window->k * window->TILE_SIZE)
	{
		if (haswallAt(cast.nextvertouchx, cast.nextvertouchy, window))
		{
            if (window->ray[col_id].is_ray_looking_left)
                cast.nextvertouchx++;
			cast.Vwallhit = true;
			cast.Vwallx = cast.nextvertouchx;
			cast.Vwally = cast.nextvertouchy;
			break;
		}
		else
		{
			cast.nextvertouchx += window->xstep;
			cast.nextvertouchy += window->ystep;
		}
	}

	return (cast);
}

void cast_rays(t_window *window, int colid)
{
	t_cast cast;

	cast.Hwallhit = false;
    cast.Vwallhit = false;
    cast.hordis = DBL_MAX;
    cast.verdis = DBL_MAX;
	cast = find_h_xy_setp(window, colid, cast);
	cast = find_h_xy_wall_hit(window, colid, cast);
	cast = find_v_xy_setp(window, colid, cast);
	cast = find_v_xy_wall_hit(window, colid, cast);
	get_dis(window, colid, cast);
}

void get_dis(t_window *window, int col_id, t_cast cast)
{
	if (cast.Hwallhit == true)
		cast.hordis = dis(window->player_x, window->player_y, cast.Hwallx, cast.Hwally);
	if (cast.Vwallhit == true)
		cast.verdis = dis(window->player_x, window->player_y, cast.Vwallx, cast.Vwally);
	if (cast.hordis < cast.verdis)
	{
		window->ray[col_id].washitver = false;
		window->ray[col_id].ray_hit_x = cast.Hwallx;
		window->ray[col_id].ray_hit_y = cast.Hwally;
		window->ray[col_id].distance = cast.hordis;
	}
	else
	{
		window->ray[col_id].washitver = true;
		window->ray[col_id].ray_hit_x = cast.Vwallx;
		window->ray[col_id].ray_hit_y = cast.Vwally;
		window->ray[col_id].distance = cast.verdis;
	}
	if (window->map->map[get_hit_pos(window, col_id, 'y')][get_hit_pos(window, col_id, 'x')] == 'D')
		window->ray[col_id].door_hit = true;
}

int get_hit_pos(t_window *window, int col_id, char c)
{
	int x;
	int y;

	if (c == 'x')
	{
		x = floor(window->ray[col_id].ray_hit_x / window->TILE_SIZE);
		if (window->ray[col_id].is_ray_looking_left && window->ray[col_id].washitver == true)
			x -= 1;
		return (x);
	}
	y = floor(window->ray[col_id].ray_hit_y / window->TILE_SIZE);
	if (window->ray[col_id].is_ray_looking_up && window->ray[col_id].washitver == false)
		y -= 1;
	return (y);
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
		window->ray[colid].door_hit = false;
		cast_rays(window, colid);
		window->ray_a += FOV_ANGLE / window->rays;
		colid++;
	}
}
