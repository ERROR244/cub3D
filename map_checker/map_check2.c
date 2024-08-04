/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:40 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/04 18:23:41 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

//		- - -
//		- . -
//		- - -

//		-1 ↑ x ↓ +1
//		-1 ← y → +1

//	so this is all the  possible cases
// (x) (y + 1)
// (x) (y - 1)
// (x + 1) (y)
// (x - 1) (y)
// (x + 1) (y + 1)
// (x - 1) (y - 1)
// (x - 1) (y + 1)
// (x + 1) (y - 1)

bool	surrounded_with_only_spaces_and_walls(char **map, int x, int y)
{
	int		lines;

	//		  -  
	//		- . -
	//		  -  

	lines = array_size(map);	
	if (map[x][y + 1] != '1' && map[x][y + 1] != ' ' && map[x][y + 1] != '\0')
		return (false);
	if (y - 1 >= 0 && map[x][y - 1] != '1' && map[x][y - 1] != ' ' && map[x][y - 1] != '\0')
		return (false);
	if (x + 1 < lines && map[x + 1][y] != '1' && map[x + 1][y] != ' ' && map[x + 1][y] != '\0')
		return (false);
	if (x - 1 >= 0 && map[x - 1][y] != '1' && map[x - 1][y] != ' ' && map[x - 1][y] != '\0')
		return (false);
	
	//		-   -
	//		  .  
	//		-   -
	
	if (x + 1 < lines && map[x + 1][y + 1] != '1' && map[x + 1][y + 1] != ' ' && map[x + 1][y + 1] != '\0')
		return (false);
	if (y - 1 >= 0 && x - 1 >= 0 && map[x - 1][y - 1] != '1' && map[x - 1][y - 1] != ' ' && map[x - 1][y - 1] != '\0')
		return (false);
	if (x - 1 >= 0 && map[x - 1][y + 1] != '1' && map[x - 1][y + 1] != ' ' && map[x - 1][y + 1] != '\0')
		return (false);
	if (x + 1 < lines && y - 1 >= 0 && map[x + 1][y - 1] != '1' && map[x + 1][y - 1] != ' ' && map[x + 1][y - 1] != '\0')
		return (false);
	return (true);
}

void    free_and_check(char **map)
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
        {
            printf(":%c:\n", map[i][size]);
        	flag = false;
        }
        free(map[i]);
        i++;
    }
    free(map);
	if (flag == false)
		the_map_is_invalid();
}
