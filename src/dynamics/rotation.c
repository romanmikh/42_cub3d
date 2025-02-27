#include "cub3d.h"

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
