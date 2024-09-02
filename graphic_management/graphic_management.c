#include "../include/cub.h"

void clear_image(t_window *window, int width, int height, int color)
{
    int x;
    int y;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            my_mlx_pixel_put(window, x, y, color);
            x++;
        }
        y++;
    }
}

int	my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < window->window_width && y >= 0 && y < window->window_hight) {
        dst = window->img->addr + (y * window->img->line_length + x * (window->img->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
	return (0);
}
// int put_img(t_window *window)
// {
//     int ret;
//
//     ret = 0;
//     mlx_clear_window(window->mlx, window->window);
//     draw_mini_map(window);
//     ret = render3d(window);
//
// 	// if (window->update_waidow == true)
// 		mlx_put_image_to_window(window->mlx, window->window, window->img->img, 0, 0);
//     return (ret);
// }

void	graphic_management(t_window *window)
{
	window->mouse_x = 0;
	window->mouse_y = 0;
	window->minimap = 0.5;
	window->pa = PI/2;
	window->wall_wigth = 1;
	window->window_width = 1400;
	window->window_hight = 900;
	window->update_waidow = true;
	window->rays = window->window_width / window->wall_wigth;
	window->mlx = mlx_init();
	window->window = mlx_new_window(window->mlx, window->window_width, window->window_hight, "cub3D");
	window->ray = malloc(sizeof(*(window->ray)) * window->rays);
	window->img = malloc(sizeof(*(window->img)));
	if (window->img == NULL) {
	    fprintf(stderr, "Failed to allocate memory for img.\n");
	    exit(EXIT_FAILURE);
	}
	window->img->img = mlx_new_image(window->mlx, window->window_width, window->window_hight);
	if (window->img->img == NULL) {
	    fprintf(stderr, "Failed to create image.\n");
	    exit(EXIT_FAILURE);
	}
	// window->img->tmp_img = mlx_new_image(mlx, window->window_width, window->window_hight);
	window->img->addr = mlx_get_data_addr(window->img->img, &window->img->bits_per_pixel, &window->img->line_length, &window->img->endian);
	if (window->img->addr == NULL) {
	    fprintf(stderr, "Failed to get image data address.\n");
	    exit(EXIT_FAILURE);
	}
    key_hook(6, window, 1);
	// mouse_hook(1, window);
	// mlx_key_hook(window->window, key_hook, window);
    // mlx_loop_hook(window->mlx, put_img, window);
	// mlx_mouse_get_pos(window->mlx, window->window, (int)&window->player_x, (int)&window->player_y);
	// mlx_mouse_hook(window->window, mouse_hook, window);
	mlx_mouse_get_pos(window->mlx, window->window, &window->mouse_x, &window->mouse_y);
	printf("button: 0, x: %d, y: %d\n", window->mouse_x ,window->mouse_y);
	mlx_hook(window->window, 02, 1L<<0, key_hook, window);
	mlx_hook(window->window, 17, 0L, close_window, window);
    mlx_loop(window->mlx);
	// draw_2D_map(window);
}
