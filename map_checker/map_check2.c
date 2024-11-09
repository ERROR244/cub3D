/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:40 by ksohail-          #+#    #+#             */
/*   Updated: 2024/11/09 14:43:08 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int    ft_ft_atoi(char *ptr)
{
    int    num;
    int    i;

    i = 0;
    while (ptr[i] == ' ')
        i++;
    if (!ptr[i])
        return (-1);
    while (ptr[i] && ptr[i] != ' ')
    {
        if (ft_isdigit(ptr[i]) == 0)
            return (-1);
        i++;
    }
    while (ptr[i])
    {
        if (ptr[i] != ' ')
            return (-1);
        i++;
    }
    num = ft_atoi(ptr);
    if (num < 0 || num > 255)
        return (-1);
    return (num);
}

bool	surrounded_with_only_spaces_and_walls(char **map, int x, int y,
		int lines)
{
	if (map[x][y + 1] != '0' && map[x][y + 1] != '1' && map[x][y + 1] != 'D'
		&& map[x][y + 1] != 'N')
		return (false);
	if (y - 1 < 0 || (map[x][y - 1] != '0' && map[x][y - 1] != '1' && map[x][y
		- 1] != 'N' && map[x][y - 1] != 'D'))
		return (false);
	if (x + 1 >= lines || (map[x + 1][y] != '0' && map[x + 1][y] != '1' && map[x
		+ 1][y] != 'N' && map[x + 1][y] != 'D'))
		return (false);
	if (x - 1 < 0 || (map[x - 1][y] != '0' && map[x - 1][y] != '1' && map[x
		- 1][y] != 'N' && map[x - 1][y] != 'D'))
		return (false);
	return (true);
}

void	check_map_end(char **map)
{
	bool	flag;
	int		i;
	int		size;

	i = 0;
	flag = true;
	while (map && *map && map[i])
	{
		size = ft_strlen(map[i]) - 1;
		if (map[i][size] != '1' && map[i][size] != ' ')
			flag = false;
		i++;
	}
	if (flag == false)
		the_map_is_invalid();
}

int	create_trgb(int t, int *nums)
{
	if (!nums)
		the_textures_is_invalid();
	return (t << 24 | nums[0] << 16 | nums[1] << 8 | nums[2]);
}
