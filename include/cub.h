/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:59:21 by error01           #+#    #+#             */
/*   Updated: 2024/10/11 19:16:22 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define PI 3.141592
# define TWO_PI 6.28318530
# define FOV_ANGLE (60 * (PI / 180))
# define MINI_MAP_SIZE 6
# define MAP_HEIGHT 900
# define MAP_WIDTH 1400
# define SIZE 100
# define MSPEED 2
#define COLLISION_BUFFER 10



// # include <mlx.h>
# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

typedef enum
{
	North,
	South,
	East,
	West,
	None
}				orientation;

typedef enum
{
	moveForWard,
	moveBackward,
	moveRight,
	moveLeft,
	viewRight,
	viewLeft,
	OpenClose,
	escExit,
	none
}				events;

typedef struct s_map
{
	char		*texture_no;
	char		*texture_so;
	char		*texture_we;
	char		*texture_ea;

	void		*img_no;
	void		*img_so;
	void		*img_we;
	void		*img_ea;
	void		*door;

	int			*ceiling_color;
	int			*floor_color;

	int			*array_length;

	char		**map;
}				t_map;

typedef struct s_ray
{
	double		ray_a;
	double		ray_hit_x;
	double		ray_hit_y;
	double		distance;

	bool		washitver;
	bool		door_hit;

	bool		is_ray_looking_down;
	bool		is_ray_looking_up;
	bool		is_ray_looking_right;
	bool		is_ray_looking_left;

	void		*img;

	int			col_id;
}				t_ray;

typedef struct s_img
{
	void		*img;
	void		*tmp_img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct
{
	double		hordis;
	double		verdis;
	double		Hwallx;
	double		Hwally;
	double		Vwallx;
	double		Vwally;
	double		nexthorztouchx;
	double		nexthorztouchy;
	double		nextvertouchx;
	double		nextvertouchy;
	bool		Hwallhit;
	bool		Vwallhit;
}				t_cast;

typedef struct s_move
{
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				rotate_left;
	int				rotate_right;
}	t_move;


typedef struct window
{
	t_map		*map;
	void		*free_space;
	void		*wall;
	void		*img2;
	void		*player;
	void		*mlx;
	void		*window;

	double		minimap;

	double		player_x;
	double		player_y;
	double		pa;
	double		ray_a;

	t_ray		*ray;
	t_img		*img;
	t_img		*texture;

	int			window_width;
	int			window_hight;
	int			wall_wigth;
	int			rays;

	double		xfirststep;
	double		yfirststep;
	double		xstep;
	double		ystep;

	int			mouse_x;
	int			mouse_y;

	int			TILE_SIZE;

	orientation	spawning_dir;

	t_move move;

	int			i;
	int			k;
}				t_window;

// tmp
void			print_array(char **str);
void			free_array(char **str);
void			print_array_in_one_line(char **str);
void			modify_and_restore(char **map, int rows, int cols);
void			print_array_of_int(int *color);
char			**copy_array(char **original, int rows, int cols);
void			exit_game(t_window *window);

// error
void			the_map_is_invalid(void);
void			invalid_file_name1(void);
void			invalid_file(void);
void			invalid_arg(void);
void			the_textures_is_invalid(void);
void			exit_error(char *str);

char			**return_map(int fd, char *ptr, char *str, int i);
char			**name_check(char *str);
char			*ft_strjoin3(char const *s1, char c, char const *s2);
void			the_map_is_invalid(void);
void			invalid_file_name1(void);

// map check
void			map_check(t_map *map, char **str, t_window *window);
void			check_texture_and_color(t_map *map, char **str);
int				array_size(char **str);
void			check_characters(char **map, t_window *window, int i, int k);
void			is_the_map_surrounded_by_walls(char **map);
bool			surrounded_with_only_spaces_and_walls(char **map, int x, int y,
					int lines);
void			check_map_end(char **map);
char			**get_map_updated(char **ptr);

// graphic_management
void			graphic_management(t_window *w);
int				close_window(t_window *window);
double			to_rad(double deg);
double			to_deg(double rad);
void			rays_3d_cast(t_window *window);
int				render3d(t_window *window, int ret, int i);
bool			has_wall_at(long x, long y, t_window *window);
int				my_mlx_pixel_put(t_window *window, int x, int y, int color);
void			clear_image(t_window *window, int width, int height, int color);
unsigned int	git_tpixel(t_window *window, int x, int y);
int				get_hit_pos(t_window *window, int col_id, char c);
t_cast			get_dis(t_window *window, int col_id, t_cast cast);
t_cast			find_h_xy_setp(t_window *window, int col_id, t_cast cast);
t_cast			find_v_xy_setp(t_window *window, int col_id, t_cast cast);
double			get_spawninig_orientation(orientation ori);
int				create_trgb(int t, int r, int g, int b);



// minimap
int				draw_mini_map(t_window *window);

// 2D
int				draw_squar(t_window *window, int y, int x, int color);
int				draw_map(t_window *window);
void			draw_2D_map(t_window *window);
void			dda_for_line(double X0, double Y0, double X1, double Y1,
					t_window *window);

// events
events			get_event(int keycode);
int				key_hook(int keycode, t_window *window);

int				handle_door(events event, t_window *window);
int				handle_rotate(t_window *window);
int				key_release(int keycode, t_window *window);
int				key_press(int keycode, t_window *window);
int				handle_fb_move(t_window *window);
int				handle_lr_move(t_window *window);


int				handle_event(events event, t_window *window);
int				handle_mouse(t_window *window);

#endif
