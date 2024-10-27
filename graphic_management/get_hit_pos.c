/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:01:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 19:38:19 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
