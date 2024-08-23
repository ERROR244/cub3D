#include "../include/cub.h"

inline double to_rad(double deg)
{
	return (deg * (PI / 180.0));
}

inline double to_deg(double rad)
{
	return (rad * (180.0 / PI));
}

void	graphic_management(t_window *window)
{
	draw_2D_map(window);
}
