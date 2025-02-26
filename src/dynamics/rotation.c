#include "cub3d.h"

// static int	rotate_left_right(t_data *data, double rot_angle)
// {
// 	t_player	*p;
// 	double		tmp_x;

// 	p = &data->player;
// 	tmp_x = p->dir_x;
// 	p->dir_x = p->dir_x * cos(rot_angle) - p->dir_y * sin(rot_angle);
// 	p->dir_y = tmp_x * sin(rot_angle) + p->dir_y * cos(rot_angle);
// 	tmp_x = p->plane_x;
// 	p->plane_x = p->plane_x * cos(rot_angle) - p->plane_y * sin(rot_angle);
// 	p->plane_y = tmp_x * sin(rot_angle) + p->plane_y * cos(rot_angle);
// 	return (1);
// }

// int	rotate_player(t_data *data, double rot_dir)
// {
// 	int		moved;
// 	double	rot_angle;

// 	moved = 0;
// 	rot_angle = ROTATION_ANGLE * rot_dir;
// 	moved += rotate_left_right(data, rot_angle);   
// 	return (moved);
// }

/*
# x' = x * cos(θ) - y * sin(θ)
# y' = x * sin(θ) + y * cos(θ)
*/

int	rotate_player(t_data *data, double rot_dir)
{
	t_player	*p;
	double		rot_angle;
	double		tmp_x;

	p = &data->player;
	rot_angle = ROTATION_ANGLE * rot_dir;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot_angle) - p->dir_y * sin(rot_angle);
	p->dir_y = tmp_x * sin(rot_angle) + p->dir_y * cos(rot_angle);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_angle) - p->plane_y * sin(rot_angle);
	p->plane_y = tmp_x * sin(rot_angle) + p->plane_y * cos(rot_angle);
	return (1);
}
