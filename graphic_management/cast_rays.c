/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:34:52 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	cast_rays(t_window *window, int colid)
{
	t_cast	cast;
	int		y;
	int		x;

	cast.hwallhit = false;
	cast.vwallhit = false;
	cast.hordis = 1.797693e+308;
	cast.verdis = 1.797693e+308;
	cast = find_h_xy_setp(window, colid, cast);
	cast = find_h_xy_wall_hit(window, colid, cast);
	cast = find_v_xy_setp(window, colid, cast);
	cast = find_v_xy_wall_hit(window, colid, cast);
	cast = get_dis(window, colid, cast);
	y = get_hit_pos(window, colid, 'y');
	x = get_hit_pos(window, colid, 'x');
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

void	git_ray_img(t_window *window, int i)
{
	if (!window->ray[i].washitver && window->ray[i].is_ray_looking_up)
		window->ray[i].img = &window->texture[0];
	else if (!window->ray[i].washitver && window->ray[i].is_ray_looking_down)
		window->ray[i].img = &window->texture[1];
	else if (window->ray[i].washitver && window->ray[i].is_ray_looking_left)
		window->ray[i].img = &window->texture[2];
	else if (window->ray[i].washitver && window->ray[i].is_ray_looking_right)
		window->ray[i].img = &window->texture[3];
	if (window->ray[i].door_hit == true)
		window->ray[i].img = &window->texture[4];
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
		w->ray[i].is_ray_looking_right = (w->ray[i].ray_a < 0.5 * PI
				|| w->ray[i].ray_a > 1.5 * PI);
		w->ray[i].is_ray_looking_left = !w->ray[i].is_ray_looking_right;
		w->ray[i].door_hit = false;
		cast_rays(w, i);
		git_ray_img(w, i);
		w->ray_a += FOV_ANGLE / w->rays;
		i++;
	}
}
