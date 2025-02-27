#include "cub3d.h"

void	init_ray(t_ray *ray)
{
	ray->field_of_view = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_hit_x_coord = 0;
	ray->hit_horiz_wall = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

static void	init_map_data(t_map_data *map_data)
{
	map_data->fd = 0;
	map_data->line_count = 0;
	map_data->path = NULL;
	map_data->file = NULL;
	map_data->height = 0;
	map_data->width = 0;
	map_data->end_of_map_line_index = 0;
}

static void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rot_dir = 0;
}

void	init_main(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	init_player(&data->player);
	init_text_data(&data->text_data);
	data->map = NULL;
	init_map_data(&data->map_data);
	data->texture_pixels = NULL;
	data->textures = NULL;
}
