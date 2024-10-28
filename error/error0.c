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

void	invalid_file_name1(void)
{
	printf("Error\n		invalid file name\n");
	exit(EXIT_FAILURE);
}

void	invalid_file(void)
{
	printf("Error\n		invalid file\n");
	exit(EXIT_FAILURE);
}

void	exit_error(char *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}
