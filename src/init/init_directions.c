#include "cub3d.h"

static void	init_player_direction_n_s(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;  // starting facing north -> -1 in y direction
		player->plane_x = 0.66;  // so plane of view will be the x axis (perpendicular to dir_y). 0.66 = half of field of view. Change to other values & recompile to visualise this
		player->plane_y = 0;
	}
	else if (player->dir == 'S')
	{
		player->dir_x = 0; 
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

static void	init_player_direction_e_w(t_player *player)
{
	if (player->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else
		return ;
}

void	init_player_direction(t_data *data)
{
	init_player_direction_n_s(&data->player);
	init_player_direction_e_w(&data->player);
}
