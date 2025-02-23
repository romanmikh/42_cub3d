#include "cub3d.h"

static int	count_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		err_msg(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

static void	cub_file_to_2d_arr(int row, int col, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map_data.fd);
	while (line != NULL)
	{
		data->map_data.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map_data.file[row])
		{
			err_msg(NULL, ERR_MALLOC, 0);
			return (ft_free_2d_arr((void **)data->map_data.file));
		}
		while (line[i] != '\0')
			data->map_data.file[row][col++] = line[i++];
		data->map_data.file[row++][col] = '\0';
		col = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map_data.fd);
	}
	data->map_data.file[row] = NULL;
	// ft_print_2d_arr(data->map_data.file, "data->map_data.file");
}

void	parse_input(char *path, t_data *data)
{
	int		row;
	int		i;
	size_t	col;

	i = 0;
	row = 0;
	col = 0;
	data->map_data.path = path;
	data->map_data.line_count = count_lines(path);
	data->map_data.file = ft_calloc(data->map_data.line_count \
			+ 1, sizeof(char *));
	if (!(data->map_data.file))
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
	data->map_data.fd = open(path, O_RDONLY);
	if (data->map_data.fd < 0)
		err_msg(path, strerror(errno), FAILURE);
	else
	{
		cub_file_to_2d_arr(row, col, i, data);
		close(data->map_data.fd);
	}
}