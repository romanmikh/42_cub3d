#include "cub3d.h"

static char	*parse_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;  // copy texture path
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t')) // skip trailing spaces 
		j++;
	if (line[j] && line[j] != '\n')  // if extra content after path, it's an error
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	parse_texture_orientations(t_text_data *textures, char *line, int j)
{
	char **tex;
	
	tex = NULL;
	if (line[j + 2] && ft_is_print(line[j + 2])) 
		return (ERR);
	if (ft_strncmp(&line[j], "NO", 2) == 0)
		tex = &textures->north;
	else if (ft_strncmp(&line[j], "SO", 2) == 0)
		tex = &textures->south;
	else if (ft_strncmp(&line[j], "WE", 2) == 0)
		tex = &textures->west;
	else if (ft_strncmp(&line[j], "EA", 2) == 0)
		tex = &textures->east;
	else
		return (ERR);
	if (!*tex)
		*tex = parse_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

static int	parse_cub_file(t_data *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n') // skip whitespaces
		j++;
	if (ft_is_print(map[i][j]) && !ft_is_digit(map[i][j])) // if texture/colour identifier 
	{
		if (map[i][j + 1] && ft_is_print(map[i][j + 1]) // if next also printable & not digit, it's a texture
			&& !ft_is_digit(map[i][j]))
		{
			if (parse_texture_orientations(&data->text_data, map[i], j) == ERR)
				return (err_msg(data->map_data.path, ERR_TEX_INVALID, FAILURE));
			return (BREAK);
		}	
		else  // it's floor/ceiling
		{
			if (set_ceiling_floor_colours(data, &data->text_data, map[i], j) == ERR)
				return (FAILURE);
			return (BREAK);
		}	
	}
	else if (ft_is_digit(map[i][j])) // then it's map layout
	{
		if (create_map(data, map, i) == FAILURE)
			return (err_msg(data->map_data.path, ERR_INVALID_MAP, FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

// input is entire cub file as 2d arr 
int	process_cub_file(t_data *data, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])  // for each square on map
		{
			ret = parse_cub_file(data, map, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
