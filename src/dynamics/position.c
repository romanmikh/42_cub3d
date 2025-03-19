#include "cub3d.h"

static bool	is_valid_wall_collision(t_data *data, double x, double y)
{
	if (data->map[(int)y][(int)x] == '0')
		return (true);
	return (false);
}

static bool	is_valid_position(t_data *data, double x, double y)
{
	if (is_valid_wall_collision(data, x, y))
		return (true);
	return (false);
}

int	is_valid_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_position(data, new_x, data->player.pos_y))
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_position(data, data->player.pos_x, new_y))
	{
		data->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
