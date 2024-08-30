/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/08/28 17:56:07 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	**return_map(int fd, int i)
{
	char	*ptr;
	char	*str;
	char	**sptr;

	ptr = get_next_line(fd);
	if (ptr == NULL)
		the_map_is_invalid();
	str = ptr;
	while (ptr != NULL)
	{
		ptr = get_next_line(fd);
		if (i > 5 && ptr && ptr[0] == '\n')
		{
			while (ptr && ptr[0] == '\n')
			{
				free(ptr);
				ptr = get_next_line(fd);
			}
			if (ptr)
			{
				free(ptr);
				the_map_is_invalid();
			}
			else
				break ;
		}
		if (ptr && ptr[0] != '\n')
			i++;
		str = ft_strjoin(str, ptr);
	}
	close(fd);
	sptr = ft_split(str, '\n');
	free(str);
	return (sptr);
}

char	**name_check(char *str)
{
	int	i;

	i = 0;
	while (str[0] && str[i + 1])
		i++;
	if (str[i--] != 'b')
		invalid_file_name1();
	if (str[i--] != 'u')
		invalid_file_name1();
	if (str[i--] != 'c')
		invalid_file_name1();
	if (str[i--] != '.')
		invalid_file_name1();
	i = open(str, O_RDONLY);
	if (i == -1)
		invalid_file_name1();
	return (return_map(i, 0));
}

void exit_game(t_window *window)
{
	t_map *map;

	map = window->map;
    free(map->texture_no);
	free(map->texture_so);
	free(map->texture_we);
	free(map->texture_ea);
    free(map->floor_color);
    free(map->ceiling_color);
    free_array(map->map);
}

int main(int ac, char **av)
{
	t_window	window;
    t_map       map;
    char		**str;

	if (ac != 2)
		invalid_arg();
	str = name_check(av[1]);
	if (str == 0)
    {
		the_map_is_invalid();
    }
	window.i = 0;
	window.k = 0;
    map_check(&map, str, &window);
	window.map = &map;
	window.playermini_x = window.player_x;
	window.playermini_y = window.player_y;
	graphic_management(&window);



	// printf("------------------------------>%s\n", map.texture_no);
	// printf("------------------------------>%s\n", map.texture_so);
	// printf("------------------------------>%s\n", map.texture_we);
	// printf("------------------------------>%s\n", map.texture_ea);
	//
    // print_array_of_int(map.ceiling_color);
    // print_array_of_int(map.floor_color);
	//
    // print_array(map.map);

	exit_game(&window);

    return (0);
}
