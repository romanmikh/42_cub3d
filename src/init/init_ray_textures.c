#include "cub3d.h"

void	init_ray_cast_info(int x, t_ray *ray, t_player *player)
{
	init_ray(ray);  // Reset the ray's values
	ray->field_of_view = 2 * x / (double)WIN_WIDTH - 1; // Convert screen column x to a normalisedf position in player's POV (-1 left-most col and 1 right-most col)
	// imagine looking at the map from top-down 
	// each ray (=x=column from L -> R of screen) from the player's POV will have its own ray->dir_x/_y 
	// easiest to see if we calculate the first x's (left-most column on screen) dir_x/_y assuming player starts facing N
	// player->dir_x = 0, player->dir_y = -1, plane_x = 0.66, plane_y = 0. field_of_view = -1
	// then dir_x = 0 + 0.66*-1 = -0.66, dir_y = -1 + 0.66*-1 = -1.66
	// so left-most ray from player's POV will move in direction (-0.66, -1.66), so it goes slightly left and up, which makes sense from top-down view
	// similarly, right-most ray will move in direction (0.66, 1.66), so it goes slightly right and up. Same logic for all rays/columns between
	ray->dir_x = player->dir_x + player->plane_x * ray->field_of_view;
	ray->dir_y = player->dir_y + player->plane_y * ray->field_of_view;
	ray->map_x = (int)player->pos_x; // Convert player's floating-point position to integer map coordinates
	ray->map_y = (int)player->pos_y; // tells us in which grid cell the ray starts in
	// deltadist_x/_y is how far the ray moves in x and y per step (distance to next grid line in x/y direction)
	// suppose dir_x = 1, then 1/1 = 1 and we need to walk 1 unit from ray's POV to reach grid vertical line
	// suppose dir_x = 0, 1/0 = inf so we never get to the next verical grid line
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y); 
}

static int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_img(data, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * data->text_data.size * data->text_data.size);  // width * height * int buffer => 2D image
	if (!buffer)
		graceful_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	y = 0; // copy pixel data from image into buffer
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
	// free temp image after copying its data
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_data *data)
{
	data->textures = ft_calloc(5, sizeof * data->textures);  // 5 instead of 4 for padding, segfault otherwise
	if (!data->textures)
		graceful_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	// load each texture into memory
	data->textures[NORTH] = xpm_to_img(data, data->text_data.north);  // format: 1D array of ints
	data->textures[SOUTH] = xpm_to_img(data, data->text_data.south);
	data->textures[EAST] = xpm_to_img(data, data->text_data.east);
	data->textures[WEST] = xpm_to_img(data, data->text_data.west);
}

void	init_text_data(t_text_data *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
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

