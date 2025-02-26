#include "cub3d.h"

static int	is_valid_map_contents(t_data *data, char **map_arr)
{
	int	i;
	int	j;

	i = 0;
	data->player.dir = '0';
	while (map_arr[i] != NULL)
	{
		j = 0;
		while (map_arr[i][j])
		{
			while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
			|| data->map[i][j] == '\r'
			|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("NESW10", map_arr[i][j])))
				return (err_msg(data->map_data.path, ERR_MAP_CHAR, FAILURE));
			if (ft_strchr("NESW", map_arr[i][j]) && data->player.dir != '0')
				return (err_msg(data->map_data.path, ERR_NUM_PLAYERS, FAILURE));
			if (ft_strchr("NESW", map_arr[i][j]) && data->player.dir == '0')
				data->player.dir = map_arr[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	is_valid_player_position(t_data *data, char **map_arr)
{
	int	i;
	int	j;

	i = (int)data->player.pos_y;
	j = (int)data->player.pos_x;
	if (ft_strlen(map_arr[i - 1]) < (size_t)j  // row above or below too short
		|| ft_strlen(map_arr[i + 1]) < (size_t)j)
		return (FAILURE);
	return (SUCCESS);
}

static int	set_player_position(t_data *data, char **map_arr)
{
	int	i;
	int	j;

	if (data->player.dir == '0')
		return (err_msg(data->map_data.path, ERR_PLAYER_DIR, FAILURE));
	i = 0;
	while (map_arr[i])
	{
		j = 0;
		while (map_arr[i][j])
		{
			if (ft_strchr("NSEW", map_arr[i][j]))
			{
				data->player.pos_x = (double)j + 0.5;
				data->player.pos_y = (double)i + 0.5;
				map_arr[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (is_valid_player_position(data, map_arr) == FAILURE)
		return (err_msg(data->map_data.path, ERR_PLAYER_POS, FAILURE));
	return (SUCCESS);
}

static int	ensure_no_trailing_map_content(t_map_data *map)
{
	int	i;
	int	j;

	i = map->end_of_map_line_index;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	is_valid_map(t_data *data, char **map_arr)
{
	if (!data->map)
		return (err_msg(data->map_data.path, ERR_MAP_MISSING, FAILURE));
	if (is_valid_map_borders(&data->map_data, map_arr) == FAILURE)
		return (err_msg(data->map_data.path, ERR_MAP_BORDERS, FAILURE));
	if (data->map_data.height < 3)
		return (err_msg(data->map_data.path, ERR_MAP_TOO_SMALL, FAILURE));
	if (is_valid_map_contents(data, map_arr) == FAILURE)
		return (FAILURE);
	if (set_player_position(data, map_arr) == FAILURE)
		return (FAILURE);
	if (ensure_no_trailing_map_content(&data->map_data) == FAILURE)
		return (err_msg(data->map_data.path, ERR_MAP_TRAIL, FAILURE));
	return (SUCCESS);
}
