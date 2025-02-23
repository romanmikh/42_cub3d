#include "cub3d.h"

static void	free_texture_data(t_text_data *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

void	ft_free_2d_arr(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

static void	free_map(t_data *data)
{
	if (data->map_data.fd > 0)
		close(data->map_data.fd);
	if (data->map_data.file)
		ft_free_2d_arr((void **)data->map_data.file);
	if (data->map)
		ft_free_2d_arr((void **)data->map);
}

int	free_data(t_data *data)
{
	if (data->textures)
		ft_free_2d_arr((void **)data->textures);
	if (data->texture_pixels)
		ft_free_2d_arr((void **)data->texture_pixels);
	free_texture_data(&data->text_data);
	free_map(data);
	return (FAILURE);
}
