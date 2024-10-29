/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalil <khalil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:59:21 by error01           #+#    #+#             */
/*   Updated: 2024/10/29 18:53:02 by khalil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define PI 3.141592
# define TWO_PI 6.28318530
# define FOV_ANGLE 1.04719733
# define MINI_MAP_SIZE 6
# define MAP_HEIGHT 900
# define MAP_WIDTH 1400
# define SIZE 100
# define MSPEED 2
# define COLLISION_BUFFER 10

# include "../Get-Next-Line/get_next_line.h"
# include "../Libft/libft.h"
# include <mlx.h>
// # include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

typedef enum s_orientation
{
	North,
	South,
	East,
	West,
	None
}				t_orientation;

typedef enum s_events
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
}				t_events;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_map_bounds
{
	int	xx;
	int	yy;
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
}	t_map_bounds;

typedef struct s_draw_pos
{
	int	x;
	int	y;
}	t_draw_pos;

typedef struct s_pixel
{
	int		x;
	int		y;
	int		line_length;
	int		bits_per_pixel;
	char	*src_addr;
}	t_pixel;

typedef struct s_render
{
	int		x;
	int		y;
	int		width;
	int		height;
	double	wall_hit_x;
	t_img	*img;
}	t_render;

typedef struct s_map
{
	char		*texture_no;
	char		*texture_so;
	char		*texture_we;
	char		*texture_ea;

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

	t_img		*img;

	int			col_id;
}				t_ray;

typedef struct s_cast
{
	double		hordis;
	double		verdis;
	double		hwallx;
	double		hwally;
	double		vwallx;
	double		vwally;
	double		nexthorztouchx;
	double		nexthorztouchy;
	double		nextvertouchx;
	double		nextvertouchy;
	bool		hwallhit;
	bool		vwallhit;
}				t_cast;

typedef struct s_move
{
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
}				t_move;

typedef struct window
{
	t_map			*map;
	void			*free_space;
	void			*wall;
	void			*img2;
	void			*player;
	void			*mlx;
	void			*window;

	double			minimap;

	double			player_x;
	double			player_y;
	double			pa;
	double			ray_a;

	t_ray			*ray;
	t_img			*img;
	t_img			*texture;
	t_img			*anm;

	int				window_width;
	int				window_hight;
	int				wall_wigth;
	int				rays;

	double			disp; //displane
	double			dist; //distance
	double			wl3dh; //wll3dhight
	double			xfirststep;
	double			yfirststep;
	double			xstep;
	double			ystep;

	int				mouse_x;
	int				mouse_y;

	int				tile_size;

	t_orientation	spawning_dir;

	t_move			move;

	int				i;
	int				k;

	bool			shoot;
}					t_window;

// tmp
void			print_array(char **str);
void			free_array(char **str);
void			print_array_in_one_line(char **str);
void			print_array_of_int(int *color);
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

// graphic_management
void			graphic_management(t_window *w);
void			init_data(t_window *window, int width, int height);
void			init_anm(t_window *window);
void			init_texture_anm(t_window *window);
void			init_texture(t_window *window, int width, int height);
int				close_window(t_window *window);
void			rays_3d_cast(t_window *window);
int				render3d(t_window *window, int ret, int i);
bool			has_wall_at(long x, long y, t_window *window);
int				my_mlx_pixel_put(t_window *window, int x, int y, int color);
int				get_hit_pos(t_window *window, int col_id, char c);
t_cast			get_dis(t_window *window, int col_id, t_cast cast);
t_cast			find_h_xy_setp(t_window *window, int col_id, t_cast cast);
t_cast			find_v_xy_setp(t_window *window, int col_id, t_cast cast);
double			get_spawninig_orientation(t_orientation ori);
int				create_trgb(int t, int *nums);
void			init_texture(t_window *window, int width, int height);
void			init_anm(t_window *window);
t_cast			find_v_xy_wall_hit(t_window *window, int col_id, t_cast cast);
t_cast			find_h_xy_wall_hit(t_window *window, int col_id, t_cast cast);
t_cast			find_v_xy_setp(t_window *window, int col_id, t_cast cast);
t_cast			find_h_xy_setp(t_window *window, int col_id, t_cast cast);
double			dis(double x1, double y1, double x2, double y2);
double			normalize_angle(double angle);
int				fft_abs(int x);

// minimap
int				draw_mini_map(t_window *window);
int				draw_map_square(t_window *window, int x_pos, int y_pos,
					int color);
int				draw_mini_squar(t_window *window, double y, double x,
					int color);
int				draw_mini_player(t_window *window, double y, double x,
					int color);
int				get_square_color(char map_char);

// t_events
int				handle_door(t_events event, t_window *window);
int				handle_rotate(t_window *window);
int				key_release(int keycode, t_window *window);
int				key_press(int keycode, t_window *window);
int				handle_fb_move(t_window *window);
int				handle_lr_move(t_window *window, double x, double y);
int				handle_mouse(t_window *window, int x, int y);

#endif
