#include "cub3d.h"

static int	is_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!ft_is_valid_rgb(rgb[i]))
			return (err_msg_val(rgb[i], ERR_TEX_RGB_VAL, FAILURE));
		i++;
	}
	return (SUCCESS);
}

int	is_valid_texture(t_data *data, t_text_data *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (err_msg(data->map_data.path, ERR_TEX_MISSING, FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(data->map_data.path, ERR_RGB_COLOUR_MISSING, FAILURE));
	if (is_valid_file(textures->north, false) == FAILURE
		|| is_valid_file(textures->south, false) == FAILURE
		|| is_valid_file(textures->west, false) == FAILURE
		|| is_valid_file(textures->east, false) == FAILURE
		|| is_valid_rgb(textures->floor) == FAILURE
		|| is_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	if (data->text_data.floort && data->text_data.ceilingt)
		if (is_valid_file(textures->floort, false) == FAILURE
		|| is_valid_file(textures->ceilingt, false) == FAILURE)
		return (FAILURE);
	textures->hex_floor = ft_rgb_to_hex(textures->floor);
	textures->hex_ceiling = ft_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}
