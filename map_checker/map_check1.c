/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:36 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/05 12:50:19 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	check_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' &&
					map[i][j] != 'N' && map[i][j] != ' ')
				the_map_is_invalid();
			j++;
		}
		i++;
	}
}

int longest_line_size_func(char **map)
{
	int i;
	int size;
	int line_size;
	
	size = -1;
	i = 0;
	while (map[i])
	{
		line_size = ft_strlen(map[i]);
		if (size < line_size)
			size = line_size;
		i++;
	}
	return (size);
}

char	*get_line_bigger(char *line, int size)
{
	char	*ret_line;
	char	c;
	int		i;

	i = 0;
	ret_line = malloc(sizeof(char) * (size + 1));
	while (line[i])
	{
		ret_line[i] = line[i];
		c = line[i];
		i++;
	}
	while (i < size)
	{
		ret_line[i] = c;
		i++;
	}
	ret_line[i] = '\0';
	return (ret_line);
}

char **get_map_updated(char **ptr)
{
	char	**map;
	size_t	longest_line_size;
	int		i;

	i = 0;
	longest_line_size = longest_line_size_func(ptr);
	map = malloc(sizeof(char *) * (array_size(ptr) + 1));
	while (ptr[i])
	{
		if (ft_strlen(ptr[i]) < longest_line_size)
			map[i] = get_line_bigger(ptr[i], longest_line_size);
		else
			map[i] = ft_strdup(ptr[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	is_the_map_surrounded_by_walls(char **ptr)
{
	char	**map;
	int		lines;
	int		x;
	int		y;

	x = 0;
	map = get_map_updated(ptr);
	lines = array_size(map);
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if ((map[x][y] == ' ' || ((x + 1 >= lines || x - 1 < 0) &&
					map[x][y] != '1' && map[x][y] != ' ' && map[x][y] != '\0')) &&
					surrounded_with_only_spaces_and_walls(map, x, y, lines) == false)
				the_map_is_invalid();
			y++;
		}
		x++;
	}
	free_and_check(map);
	printf("Suc\n");
}
