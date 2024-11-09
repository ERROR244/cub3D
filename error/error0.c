/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/27 18:34:50 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	the_map_is_invalid(void)
{
	printf("Error\n		The map is invalid\n");
	exit(EXIT_FAILURE);
}

void	the_textures_is_invalid(void)
{
	printf("Error\n		The Textures is invalid\n");
	exit(EXIT_FAILURE);
}

void	exit_window_with_error_norm(t_window *window, int i)
{
	if (window->texture[i].img)
		mlx_destroy_image(window->mlx, window->texture[i].img);
	if (window->img && window->img->img)
		mlx_destroy_image(window->mlx, window->img->img);
	if (window->texture)
		free(window->texture);
	if (window->anm)
		free(window->anm);
	if (window->img)
		free(window->img);
	if (window->ray)
		free(window->ray);
	if (window->window)
		mlx_destroy_window(window->mlx, window->window);
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	exit(EXIT_FAILURE);
}

void	exit_window_with_error(t_window *window, char *str)
{
	int	i;

	i = 0;
	printf("%s", str);
	if (!window->mlx)
		exit(EXIT_FAILURE);
	exit_game(window);
	while (i < 4)
	{
		if (window->texture[i].img)
			mlx_destroy_image(window->mlx, window->texture[i].img);
		if (window->anm && window->anm[i].img)
			mlx_destroy_image(window->mlx, window->anm[i].img);
		i++;
	}
	exit_window_with_error_norm(window, i);
}
