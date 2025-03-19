/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:11:34 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:11:39 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_extension(char *arg, char *ext)
{
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(arg);
	ext_len = ft_strlen(ext);
	return (len > ext_len && ft_strcmp(arg + len - ext_len, ext) == 0);
}

int	is_valid_file(char *arg, bool cub)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, ERR_FILE_MISSING, FAILURE));
	close(fd);
	if ((cub && !is_valid_extension(arg, ".cub"))
		|| (!cub && !is_valid_extension(arg, ".xpm")))
		return (err_msg(arg, ERR_FILE_FORMAT, FAILURE));
	return (SUCCESS);
}

size_t	max_line_width(t_map_data *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}

void	launch_msg(void)
{
	ft_printf(RESET "\n");
	ft_printf(CYA "====================================\n" RESET);
	ft_printf(CYA "||" MAG "         Welcome to Cub3D!      " CYA "||\n" RESET);
	ft_printf(CYA "====================================\n\n" RESET);
	ft_printf(MAG "\t W" RESET "  : Move Forward\n");
	ft_printf(MAG "\t A" RESET "  : Move Left\n");
	ft_printf(MAG "\t S" RESET "  : Move Backward\n");
	ft_printf(MAG "\t D" RESET "  : Move Right\n");
	ft_printf(MAG "\t <" RESET "  : Turn Left\n");
	ft_printf(MAG "\t >" RESET "  : Turn Right\n\n");
	ft_printf(CYA "====================================\n\n" RESET);
}

int	check_input(t_data *data, char **argv)
{
	if (is_valid_file(argv[1], true) == FAILURE)
		graceful_exit(data, FAILURE);
	parse_input(argv[1], data);
	if (process_cub_file(data, data->map_data.file) == FAILURE)
		return (free_data(data));
	if (is_valid_map(data, data->map) == FAILURE)
		return (free_data(data));
	if (is_valid_texture(data, &data->text_data) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	return (0);
}
