#include "cub3d.h"

static int	is_valid_map_top_bottom(char **map_arr, int i, int j)
{
	if (!map_arr || !map_arr[i] || !map_arr[i][j])
		return (FAILURE);
	while (map_arr[i][j] == ' ' || map_arr[i][j] == '\t'
	|| map_arr[i][j] == '\r' || map_arr[i][j] == '\v'
	|| map_arr[i][j] == '\f')
		j++;
	while (map_arr[i][j])
	{
		if (map_arr[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

static int	is_valid_map_borders_vertically(t_map_data *map, char **map_arr)
{
	int	i;
	int	j;

	j = 1;
	while (j < (map->width - 1))
	{
		i = 0;
		while (!map_arr[i][j])
			i++;
		while (i < map->height)
		{
			if (map_arr[i][j])
				i++;
			else
				break ;
		}
		i -= 1;
		if (map_arr[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	is_valid_map_borders(t_map_data *map, char **map_arr)
{
	int	i;
	int	j;

	if (is_valid_map_top_bottom(map_arr, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_arr[i]) - 1;
		if (map_arr[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (is_valid_map_top_bottom(map_arr, i, 0) == FAILURE)
		return (FAILURE);
	if (is_valid_map_borders_vertically(map, map_arr) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
