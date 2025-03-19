#include "cub3d.h"

/******************************************************************************
- field_of_view: normalises x to player's POV (-1 -> L, 1 -> R)

- dir_x/_x: imagine looking at the map from top-down 
- each ray (=x=column from L -> R of screen) has its own ray->dir_x/_y 
- example: assume player starts facing N
- p->dir_x = 0, p->dir_y = -1, plane_x = 0.66, plane_y = 0. field_of_view = -1
- then dir_x = 0 + 0.66*-1 = -0.66, dir_y = -1 + 0.66*-1 = -1.66
- so left-most ray from player's POV will move in direction (-0.66, -1.66),
- so it goes slightly left and up, which makes sense from top-down view
- similarly, right-most ray has (0.66, 1.66), so it goes slightly right and up 
- same logic for all rays/columns between

- delta_dist_x/_y: distance ray moves in x and y per step
- suppose dir_x = 1, then 1/1 = 1 and we need to walk 1 unit to reach grid
- suppose dir_x = 0, 1/0 = inf so we never get to the next verical grid line
******************************************************************************/

void	init_ray_cast_info(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);
	ray->field_of_view = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->field_of_view;
	ray->dir_y = player->dir_y + player->plane_y * ray->field_of_view;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->text_data.size * data->text_data.size);
	if (!buffer)
		graceful_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	y = 0;
	while (y < data->text_data.size)
	{
		x = 0;
		while (x < data->text_data.size)
		{
			buffer[y * data->text_data.size + x]
				= tmp.addr[y * data->text_data.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_data *data)
{
	// data->text_data.floort = "textures/mario.xpm";
	// data->text_data.ceilingt = "textures/ceiling.xpm";
	data->textures = ft_calloc(7, sizeof * data->textures);
	if (!data->textures)
		graceful_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	data->textures[NORTH] = xpm_to_img(data, data->text_data.north);
	data->textures[SOUTH] = xpm_to_img(data, data->text_data.south);
	data->textures[EAST] = xpm_to_img(data, data->text_data.east);
	data->textures[WEST] = xpm_to_img(data, data->text_data.west);
	data->textures[FLOOR] = xpm_to_img(data, data->text_data.floort);
	data->textures[CEILING] = xpm_to_img(data, data->text_data.ceilingt);
}

void	init_text_data(t_text_data *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = TEX_SIZE;
	textures->scale = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}

void	init_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		ft_free_2d_arr((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		graceful_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->texture_pixels);
		if (!data->texture_pixels[i])
			graceful_exit(data, err_msg(NULL, ERR_MALLOC, 1));
		i++;
	}
}
