/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:11:54 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:11:55 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ensure_map_enclosure(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
		|| data->map[i][j] == '\r'
		|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
			j++;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == ' '
				&& j != data->map[i][ft_strlen(data->map[i]) - 1])
				data->map[i][j] = '1';
		}
		i++;
	}
}

static int	count_map_lines(t_data *data, char **file, int i)
{
	int	line_index;
	int	j;

	line_index = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	data->map_data.end_of_map_line_index = i;
	return (i - line_index);
}

static int	copy_map_arr(t_map_data *map_data, char **map_arr, int index)
{
	int		i;
	int		j;

	map_data->width = max_line_width(map_data, index);
	i = 0;
	while (i < map_data->height)
	{
		j = 0;
		map_arr[i] = malloc(sizeof(char) * (map_data->width + 1));
		if (!map_arr[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (map_data->file[index][j] && map_data->file[index][j] != '\n')
		{
			map_arr[i][j] = map_data->file[index][j];
			j++;
		}
		while (j < map_data->width)
			map_arr[i][j++] = '\0';
		i++;
		index++;
	}
	map_arr[i] = NULL;
	return (SUCCESS);
}

static int	create_map_arr(t_data *data, char **file, int i)
{
	data->map_data.height = count_map_lines(data, file, i);
	data->map = malloc(sizeof(char *) * (data->map_data.height + 1));
	if (!data->map)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
	if (copy_map_arr(&data->map_data, data->map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	create_map(t_data *data, char **file, int i)
{
	if (create_map_arr(data, file, i) == FAILURE)
		return (FAILURE);
	ensure_map_enclosure(data);
	return (SUCCESS);
}
