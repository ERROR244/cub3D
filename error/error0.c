/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/05 11:21:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	invalid_arg(void)
{
	printf("Error\n		the number of argument is not 2\n");
	exit(EXIT_FAILURE);
}

void	the_map_is_invalid(void)
{
	printf("Error\n		The map is invalid\n");
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
