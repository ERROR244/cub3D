/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:42 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/05 09:47:57 by ksohail-         ###   ########.fr       */
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

char	*get_texture(char *str)
{
    int i;

    i = 0;
    while (str && *str && i < 2)
    {
        str++;
        i++;
    }
    while (str && *str && *str == ' ')
        str++;
    return (ft_strdup(str));
}

int *get_color(char *str)
{
    char **ptr;
    int *color;
    int i;
    int j;

    i = 0;
    j = 0;
    color = malloc(sizeof(int) * 3);
	str++;
	while (str && *str == ' ')
        str++;
    while (str[i])
    {
        if (str[i] == ',')
            j++;
        i++;
    }
    if (j != 2)
        the_map_is_invalid();
    ptr = ft_split(str, ',');
    color[0] = ft_atoi(ptr[0]);
    color[1] = ft_atoi(ptr[1]);
    color[2] = ft_atoi(ptr[2]);
    free_array(ptr);
	return (color);
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
    int i;

    i = 0;
	if (array_size(str) < 9)
        the_map_is_invalid();
    while (str[i] && i < 6)
    {
        if (ft_strncmp(str[i], "NO ", 3) == 0)
            map->texture_no = get_texture(str[i]);
        if (ft_strncmp(str[i], "SO ", 3) == 0)
            map->texture_so = get_texture(str[i]);
        if (ft_strncmp(str[i], "WE ", 3) == 0)
            map->texture_we = get_texture(str[i]);
        if (ft_strncmp(str[i], "EA ", 3) == 0)
            map->texture_ea = get_texture(str[i]);
        if (ft_strncmp(str[i], "F ", 2) == 0)
	        map->floor_color = get_color(str[i]);
        if (ft_strncmp(str[i], "C ", 2) == 0)
	        map->ceiling_color = get_color(str[i]);
        i++;
    }
	map->map = get_map(str + 6);
}
