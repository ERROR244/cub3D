/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:59:21 by error01           #+#    #+#             */
/*   Updated: 2024/09/05 17:25:06 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#define PI 3.141592
#define TWO_PI 6.28318530
#define FOV_ANGLE (60 * (PI / 180))
#define MINI_MAP_SIZE 6
#define MAP_HEIGHT 900
#define MAP_WIDTH 1400

# include "../minilibx-linux/mlx.h"
# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include <float.h>
# include <math.h>
# include <string.h>
# include <errno.h>

typedef enum {
    North, South,
    East, West,
    None
}   orientation;

typedef enum {
    moveForWard, moveBackward,
    moveRight, moveLeft,
    escExit, viewUp,
    viewDown, viewRight,
    viewLeft, OpenClose,
    none
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

typedef struct s_ray
{
    double   ray_a;
    double   ray_hit_x;
    double   ray_hit_y;
    double   distance;

    bool    washitver;

    bool is_ray_looking_down;
    bool is_ray_looking_up;
    bool is_ray_looking_right;
    bool is_ray_looking_left;

    int     col_id;
}   t_ray;

typedef struct	s_img {
    void	*img;
	void	*tmp_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct window
{
    t_map   *map;
    void	*free_space;
    void	*wall;
    void	*img2;
    void	*player;
    void	*mlx;
    void	*window;

    double minimap;

    double  player_x;
    double  player_y;
    double  pa;
    double  ray_a;

    t_ray   *ray;
    t_img   *img;

    int     window_width;
    int     window_hight;
    int     wall_wigth;
    int     rays;

    double  xfirststep;
    double  yfirststep;
    double  xstep;
    double  ystep;

    int		mouse_x;
    int		mouse_y;

    int TILE_SIZE;

    bool    update_waidow;

    orientation spawning_dir;

    int     i;
    int     k;
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
void    check_map_end(char **map);
char    **get_map_updated(char **ptr);

// graphic_management
void	graphic_management(t_window *w);
int	    close_window(t_window *window);
double  to_rad(double deg);
double  to_deg(double rad);
void    rays3D_cast(t_window *window);
int     render3d(t_window *window);
bool    haswallAt(long x, long y, t_window *window);
int	    my_mlx_pixel_put(t_window *window, int x, int y, int color);
void    clear_image(t_window *window, int width, int height, int color);
int	    kkey_hook(int keycode, t_window *window);

// minimap
int     draw_mini_map(t_window *window);


// 2D
int     draw_squar(t_window *window, int y, int x, int color);
int     draw_map(t_window *window);
void    draw_2D_map(t_window *window);
void    dda_for_line(double X0, double Y0, double X1, double Y1, t_window *window);


// events
int	    key_hook(int keycode, t_window *window);
int     handle_event(events event, t_window *window);
events  get_event(int keycode);
int     handle_mouse(t_window *window);



#endif
