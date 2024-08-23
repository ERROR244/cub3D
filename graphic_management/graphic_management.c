#include "../include/cub.h"

double to_rad(double deg)
{
	return (deg * (PI / 180.0));
}

double to_deg(double rad)
{
	return (rad * (180.0 / PI));
}

void	graphic_management(t_window *window)
{
	draw_2D_map(window);
}
