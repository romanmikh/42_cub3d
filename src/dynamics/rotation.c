#include "cub3d.h"

int	rotate_player(t_data *data, double rot_dir)
{
	t_player	*p;
	double		rot_angle;
	double		tmp_x;

	p = &data->player;
	rot_angle = ROTATION_ANGLE * rot_dir;  // larger angle per keystroke = faster rotation, so rot_angle functions like rotation speed in cub3d 
	tmp_x = p->dir_x;
	// x' = x * cos(θ) - y * sin(θ)
	// y' = x * sin(θ) + y * cos(θ)
	// this comes from https://en.wikipedia.org/wiki/Rotation_matrix
	p->dir_x = p->dir_x * cos(rot_angle) - p->dir_y * sin(rot_angle);
	p->dir_y = tmp_x * sin(rot_angle) + p->dir_y * cos(rot_angle);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_angle) - p->plane_y * sin(rot_angle);
	p->plane_y = tmp_x * sin(rot_angle) + p->plane_y * cos(rot_angle);
	return (1);
}
