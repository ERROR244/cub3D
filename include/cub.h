/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:59:21 by error01           #+#    #+#             */
/*   Updated: 2024/08/05 12:22:01 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// # include <mlx.h>
# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>

# include <mlx.h>

typedef struct s_map
{
    char *texture_no;
    char *texture_so;
    char *texture_we;
    char *texture_ea;

    int *floor_color;
    int *ceiling_color;

    char **map;
}   t_map;

typedef struct window
{
    t_map   *map;
	void	*mlx;
	void	*window;
}			t_window;

// tmp
void    print_array(char **str);
void    free_array(char **str);
void    print_array_in_one_line(char **str);
void    modify_and_restore(char **map, int rows, int cols);
void    print_array_of_int(int *color);
char**  copy_array(char** original, int rows, int cols);
void    exit_game(t_window *window);

// error
void	the_map_is_invalid(void);
void	invalid_file_name1(void);
void	invalid_file(void);
void	invalid_arg(void);

char	**return_map(int fd, int i);
char	**name_check(char *str);
char	*ft_strjoin3(char const *s1, char c, char const *s2);
void	the_map_is_invalid(void);
void	invalid_file_name1(void);

// map check
void	map_check(t_map *map, char **str);
void    check_texture_and_color(t_map *map, char **str);
int     array_size(char **str);
void	check_characters(char **map);
void	is_the_map_surrounded_by_walls(char **map);
bool	surrounded_with_only_spaces_and_walls(char **map, int x, int y, int lines);
void    free_and_check(char **map);
char    **get_map_updated(char **ptr);

// graphic_management
void	graphic_management(t_window *w);
int     close_window(t_window *window);



#endif
