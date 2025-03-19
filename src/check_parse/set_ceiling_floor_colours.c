/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ceiling_floor_colours.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:12:08 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:12:09 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*rgb_str_to_int(char **rgb_str, int *rgb_int)
{
	int		i;

	i = -1;
	while (rgb_str[++i])
	{
		rgb_int[i] = ft_atoi(rgb_str[i]);
		if (rgb_int[i] == -1 || ft_is_digit_in_str(rgb_str[i]) == false)
		{
			ft_free_2d_arr((void **)rgb_str);
			free(rgb_int);
			return (0);
		}
	}
	ft_free_2d_arr((void **)rgb_str);
	return (rgb_int);
}

static int	*set_rgb_colours(char *line)
{
	char	**rgb_str;
	int		*rgb_int;
	int		count;

	rgb_str = ft_split(line, ',');
	count = 0;
	while (rgb_str[count])
		count++;
	if (count != 3)
	{
		ft_free_2d_arr((void **)rgb_str);
		return (0);
	}
	rgb_int = malloc(sizeof(int) * 3);
	if (!rgb_int)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (0);
	}
	return (rgb_str_to_int(rgb_str, rgb_int));
}

static int	is_valid_contents(char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != ' ' && *str != ',' \
															&& *str != '\n')
			return (1);
		str++;
	}
	return (0);
}

int	set_ceiling_floor(t_data *data, t_text_data *textures, \
	char *line, int j)
{
	if (is_valid_contents(&line[j + 1]))
		return (err_msg(data->map_data.path, ERR_FLOOR_CEILING, ERR));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = set_rgb_colours(line + j + 1);
		if (textures->ceiling == 0)
			return (err_msg(data->map_data.path, ERR_FLOOR_CEILING, ERR));
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = set_rgb_colours(line + j + 1);
		if (textures->floor == 0)
			return (err_msg(data->map_data.path, ERR_FLOOR_CEILING, ERR));
	}
	else
		return (err_msg(data->map_data.path, ERR_FLOOR_CEILING, ERR));
	return (SUCCESS);
}
