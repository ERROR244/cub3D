/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:42 by ksohail-          #+#    #+#             */
/*   Updated: 2024/11/09 14:49:00 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	array_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_texture(char *str)
{
	int	i;

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

char	**get_map(char **str)
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

int	*get_color(char *str, int i, int j, int *color)
{
    char    **ptr;

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
        return (NULL);
    ptr = ft_split(str, ',');
    if (array_size(ptr) != 3)
    {
        if (ptr)
            free_array(ptr);
        return (NULL);
    }
    color = malloc(sizeof(int) * 3);
    color[0] = ft_ft_atoi(ptr[0]);
    color[1] = ft_ft_atoi(ptr[1]);
    color[2] = ft_ft_atoi(ptr[2]);
    free_array(ptr);
    if (color[0] == -1 || color[1] == -1 || color[2] == -1)
    {
        free(color);
        return (NULL);
    }
    return (color);
}

int	check_texture_and_color(t_map *map, char **str, int i)
{
	if (array_size(str) < 7)
		return (-1);
	map->floor_color = NULL;
	map->ceiling_color = NULL;
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
		if (ft_strncmp(str[i], "F ", 2) == 0 && !map->floor_color)
			map->floor_color = get_color(str[i], 0, 0, 0);
		if (ft_strncmp(str[i], "C ", 2) == 0 && !map->ceiling_color)
			map->ceiling_color = get_color(str[i], 0, 0, NULL);
		i++;
	}
	if (invalid_color(map) == -1)
		return (-1);
	map->map = get_map(str + 6);
	return (1);
}
