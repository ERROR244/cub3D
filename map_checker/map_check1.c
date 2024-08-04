/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:36 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 15:35:21 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	array_size(char **str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_texture(char *str, char *texture)
{
    if (ft_strncmp(str, texture, 3) != 0)
        the_map_is_invalid();
    str += 3;
    while (*str == ' ' || *str == '	')
        str++;
    return (ft_strdup(str));
}

char	**get_color(char *str, char color)
{
	if (str[0] != color)
        the_map_is_invalid();
	str++;
	while (*str == ' ' || *str == '	')
        str++;
	return (ft_split(str, ','));
}

char **get_map(char **str)
{
	char	**map;
	int		len;
	int		i;

	i = 0;
	len = array_size(str);
	map = malloc(sizeof(char *) * (len + 1));
	while (str[i])
	{
		map[i] = ft_strdup(str[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	check_texture_and_color(t_map *map, char **str)
{
    map->texture_no = get_texture(str[0], "NO ");
    map->texture_so = get_texture(str[1], "SO ");
    map->texture_we = get_texture(str[2], "WE ");
    map->texture_ea = get_texture(str[3], "EA ");

	map->floor_color = get_color(str[4], 'F');
	map->ceiling_color = get_color(str[5], 'C');

	map->map = get_map(str + 6);
}
