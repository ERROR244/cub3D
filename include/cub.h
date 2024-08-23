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

# ifndef PI
#define PI 3.141592
#endif

# include "../minilibx-linux/mlx.h"
# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include <math.h>


typedef enum {
    moveForWard, moveBackward,
    moveRight, moveLeft,
    escExit, viewUp,
    viewDown, viewRight,
    viewLeft,none
}   events;

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
    void	*free_space;
    void	*wall;
    void	*img2;
    void	*player;
    void	*mlx;
    void	*window;
    double dirX, dirY;          // direction vector
    double planeX, planeY;      // the 2d raycaster version of camera plane
    int     i;
    int     k;
    int     player_x;
    int     player_y;
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
void	map_check(t_map *map, char **str, t_window *window);
void    check_texture_and_color(t_map *map, char **str);
int     array_size(char **str);
void	check_characters(char **map, t_window *window);
void	is_the_map_surrounded_by_walls(char **map);
bool	surrounded_with_only_spaces_and_walls(char **map, int x, int y, int lines);
void    free_and_check(char **map);
char    **get_map_updated(char **ptr);

// graphic_management
void	graphic_management(t_window *w);
int     close_window(t_window *window);

// 2D
int	close_window(t_window *window);
int draw_squar(t_window *window, int y, int x, int color);
int draw_map(t_window *window);
void draw_2D_map(t_window *window);


// events
int	key_hook(int keycode, t_window *window);
int handle_event(events event, t_window *window);
int move(t_window *window, int i, int j);
int	p_in_the_map(char **map);
events get_event(int keycode);



#endif
