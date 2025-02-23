#include "cub3d.h"

static bool is_valid_extension(char *arg, char *ext)
{
    size_t len = ft_strlen(arg);
    size_t ext_len = ft_strlen(ext);

    return (len > ext_len && ft_strcmp(arg + len - ext_len, ext) == 0);
}

int is_valid_file(char *arg, bool cub)
{
    int fd;

    fd = open(arg, O_RDONLY);
    if (fd == -1)
        return (err_msg(arg, strerror(errno), FAILURE));  // why?
    close(fd);
    if ((cub && !is_valid_extension(arg, ".cub")) ||
        (!cub && !is_valid_extension(arg, ".xpm")))
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
	ft_printf(MAG "W" RESET ": forward\n");
	ft_printf(MAG "A" RESET ": left\n");
	ft_printf(MAG "S" RESET ": backward\n");
	ft_printf(MAG "D" RESET ": right\n");
	ft_printf(MAG "<" RESET ": turn left\n");
	ft_printf(MAG ">" RESET ": turn right\n");
	ft_printf("\n");
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