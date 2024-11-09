/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:26 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/11 11:25:30 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*get_line_sized(char *str, int line_size)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof(char ) * (line_size + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i >= 0 && str[i])
		new[i] = str[i];
	while (i < line_size)
		new[i++] = ' ';
	new[line_size] = '\0';
	free(str);
	return (new);
}

char	**get_lines_sized(t_map *map, char **str)
{
	int	line_size;
	int	size;
	int	i;

	i = 0;
	line_size = -1;
	while (str[i])
	{
		size = ft_strlen(str[i]);
		if (line_size < size)
			line_size = size;
		i++;
	}
	map->line_size = line_size;
	i = -1;
	while (++i >= 0 && str[i])
		str[i] = get_line_sized(str[i], line_size);
	return (str);
}

void	map_check(t_map *map, char **str, t_window *window)
{
	char	**lines;

	lines = get_lines_sized(map, str + 6);
	if (check_characters(lines, window, 0, 0) == -1
		|| is_the_map_surrounded_by_walls(lines) == -1
		|| check_texture_and_color(map, str, 0) == -1)
	{
		if (str)
			free_array(str);
		the_map_is_invalid();
	}
	free_array(str);
	str = NULL;
}
