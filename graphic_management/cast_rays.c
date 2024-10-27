/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:16:03 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

bool	has_wall_at(long x, long y, t_window *window)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	map_grid_index_x = (int)(x / window->tile_size);
	map_grid_index_y = (int)(y / window->tile_size);
	if (x < 0 || x > window->i * window->tile_size || y < 0 || y > window->k
		* window->tile_size)
		return (false);
	if (window->map->array_length[map_grid_index_y] <= map_grid_index_x)
		return (false);
	return (window->map->map[map_grid_index_y][map_grid_index_x] == '0'
			|| window->map->map[map_grid_index_y][map_grid_index_x] == 'A');
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

double	dis(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_cast	find_h_xy_setp(t_window *window, int col_id, t_cast cast)
{
	window->yfirststep = floor(window->player_y / window->tile_size)
		* window->tile_size;
	if (window->ray[col_id].is_ray_looking_down)
		window->yfirststep += window->tile_size;
	window->xfirststep = window->player_x + (window->yfirststep
			- window->player_y) / tan(window->ray[col_id].ray_a);
	window->ystep = window->tile_size;
	if (window->ray[col_id].is_ray_looking_up)
		window->ystep *= -1;
	window->xstep = window->tile_size / tan(window->ray[col_id].ray_a);
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

t_cast	find_v_xy_setp(t_window *window, int col_id, t_cast cast)
{
	window->xfirststep = floor(window->player_x / window->tile_size)
		* window->tile_size;
	if (window->ray[col_id].is_ray_looking_right)
		window->xfirststep += window->tile_size;
	window->yfirststep = window->player_y + (window->xfirststep
			- window->player_x) * tan(window->ray[col_id].ray_a);
	window->xstep = window->tile_size;
	if (window->ray[col_id].is_ray_looking_left)
		window->xstep *= -1;
	window->ystep = window->tile_size * tan(window->ray[col_id].ray_a);
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

t_cast	find_h_xy_wall_hit(t_window *window, int col_id, t_cast cast)
{
	while (cast.nexthorztouchx >= 0 && cast.nexthorztouchy >= 0
		&& cast.nexthorztouchx < window->i * window->tile_size
		&& cast.nexthorztouchy < window->k * window->tile_size)
	{
		if (!has_wall_at(cast.nexthorztouchx, cast.nexthorztouchy, window))
		{
			if (window->ray[col_id].is_ray_looking_up)
				cast.nexthorztouchy++;
			cast.hwallhit = true;
			cast.hwallx = cast.nexthorztouchx;
			cast.hwally = cast.nexthorztouchy;
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

t_cast	find_v_xy_wall_hit(t_window *window, int col_id, t_cast cast)
{
	while (cast.nextvertouchx >= 0 && cast.nextvertouchy >= 0
		&& cast.nextvertouchx < window->i * window->tile_size
		&& cast.nextvertouchy < window->k * window->tile_size)
	{
		if (!has_wall_at(cast.nextvertouchx, cast.nextvertouchy, window))
		{
			if (window->ray[col_id].is_ray_looking_left)
				cast.nextvertouchx++;
			cast.vwallhit = true;
			cast.vwallx = cast.nextvertouchx;
			cast.vwally = cast.nextvertouchy;
			break ;
		}
		else
		{
			cast.nextvertouchx += window->xstep;
			cast.nextvertouchy += window->ystep;
		}
	}
	return (cast);
}

void	cast_rays(t_window *window, int colid)
{
	t_cast	cast;

	cast.hwallhit = false;
	cast.vwallhit = false;
	cast.hordis = 1.797693e+308;
	cast.verdis = 1.797693e+308;
	cast = find_h_xy_setp(window, colid, cast);
	cast = find_h_xy_wall_hit(window, colid, cast);
	cast = find_v_xy_setp(window, colid, cast);
	cast = find_v_xy_wall_hit(window, colid, cast);
	cast = get_dis(window, colid, cast);

	int y = get_hit_pos(window, colid, 'y');
	int x = get_hit_pos(window, colid, 'x');

	if (window->map->map[y][x] == 'D')
		window->ray[colid].door_hit = true;
}

t_cast	get_dis(t_window *window, int col_id, t_cast cast)
{
	if (cast.hwallhit == true)
		cast.hordis = dis(window->player_x, window->player_y, cast.hwallx,
				cast.hwally);
	if (cast.vwallhit == true)
		cast.verdis = dis(window->player_x, window->player_y, cast.vwallx,
				cast.vwally);
	if (cast.hordis < cast.verdis)
	{
		window->ray[col_id].washitver = false;
		window->ray[col_id].ray_hit_x = cast.hwallx;
		window->ray[col_id].ray_hit_y = cast.hwally;
		window->ray[col_id].distance = cast.hordis;
	}
	else
	{
		window->ray[col_id].washitver = true;
		window->ray[col_id].ray_hit_x = cast.vwallx;
		window->ray[col_id].ray_hit_y = cast.vwally;
		window->ray[col_id].distance = cast.verdis;
	}
	return (cast);
}

int	get_hit_pos(t_window *window, int col_id, char c)
{
	int	x;
	int	y;

	if (c == 'x')
	{
		x = floor(window->ray[col_id].ray_hit_x / window->tile_size);
		if (window->ray[col_id].is_ray_looking_left
			&& window->ray[col_id].washitver == true && x != 0)
			x -= 1;
		return (x);
	}
	y = floor(window->ray[col_id].ray_hit_y / window->tile_size);
	if (window->ray[col_id].is_ray_looking_up
		&& window->ray[col_id].washitver == false && y != 0)
		y -= 1;
	return (y);
}

void git_ray_img(t_window *window, int i)
{
	if (window->ray[i].washitver && window->ray[i].is_ray_looking_right)
		window->ray[i].img = &window->texture[0];							 // window->map->img_no;
	else if (window->ray[i].washitver && window->ray[i].is_ray_looking_left)
		window->ray[i].img = &window->texture[1];							 // window->map->img_so;
	if (!window->ray[i].washitver && window->ray[i].is_ray_looking_up)
		window->ray[i].img = &window->texture[2];							 // window->map->img_we;
	else if (!window->ray[i].washitver
		&& window->ray[i].is_ray_looking_down)
		window->ray[i].img = &window->texture[3];							 // window->map->img_ea;
	if (window->ray[i].door_hit == true)
		window->ray[i].img = &window->texture[4];							 // window->map->door;
}

void	rays_3d_cast(t_window *window)
{
	t_window	*w;
	int			i;

	i = 0;
	w = window;
	w->ray_a = normalize_angle(w->pa - (FOV_ANGLE / 2));
	while (i < w->rays)
	{
		w->ray[i].ray_a = normalize_angle(w->ray_a);
		w->ray[i].col_id = i;
		w->ray[i].is_ray_looking_down = (w->ray[i].ray_a > 0
				&& w->ray[i].ray_a < PI);
		w->ray[i].is_ray_looking_up = !w->ray[i].is_ray_looking_down;
		w->ray[i].is_ray_looking_right = (w->ray[i].ray_a < 0.5
				* PI || w->ray[i].ray_a > 1.5 * PI);
		w->ray[i].is_ray_looking_left = !w->ray[i].is_ray_looking_right;
		w->ray[i].door_hit = false;
		cast_rays(w, i);
		git_ray_img(w, i);
		w->ray_a += FOV_ANGLE / w->rays;
		i++;
	}
}
