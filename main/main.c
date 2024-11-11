/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalil <khalil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:19:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/30 12:52:39 by khalil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	**freed_split(char *str, char c)
{
	char	**sptr;

	sptr = ft_split(str, c);
	free(str);
	return (sptr);
}

char	**return_map(int fd, char *ptr, char *str, int i)
{
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
				the_map_is_cutted_slices(ptr, str, fd);
			else
				break ;
		}
		if (ptr && ptr[0] != '\n')
			i++;
		str = ft_strjoin(str, ptr);
	}
	return (freed_split(str, '\n'));
}

char	**name_check(char *str)
{
	char	**sptr;
	char	*ptr;
	int		i;

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
	ptr = get_next_line(i);
	if (ptr == NULL)
		the_map_is_invalid();
	sptr = return_map(i, ptr, ptr, 0);
	close(i);
	return (sptr);
}

void	exit_game(t_window *window)
{
	t_map	*map;

	map = window->map;
	if (!map)
		return ;
	if (map->texture_no)
		free(map->texture_no);
	if (map->texture_so)
		free(map->texture_so);
	if (map->texture_we)
		free(map->texture_we);
	if (map->texture_ea)
		free(map->texture_ea);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
	if (map->map)
		free_array(map->map);
	map->map = NULL;
}

int	main(int ac, char **av)
{
	t_window	window;
	t_map		map;
	char		**str;

	if (ac != 2)
		invalid_arg();
	str = name_check(av[1]);
	if (str == 0)
		the_map_is_invalid();
	map.ceiling_color = NULL;
	map.floor_color = NULL;
	map.texture_ea = NULL;
	map.texture_no = NULL;
	map.texture_so = NULL;
	map.texture_we = NULL;
	map.map = NULL;
	window.i = 0;
	window.k = 0;
	window.tile_size = 32;
	map_check(&map, str, &window);
	window.map = &map;
	graphic_management(&window);
	exit_game(&window);
	return (0);
}
