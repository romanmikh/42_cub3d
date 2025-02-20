#include "cub3d.h"

static void	print_controls(void)
{
	printf(RESET "\n");
	printf(PURPLE "W" RESET ": forward\n");
	printf(PURPLE "A" RESET ": left\n");
	printf(PURPLE "S" RESET ": backward\n");
	printf(PURPLE "D" RESET ": right\n");
	printf(PURPLE "<" RESET ": turn left\n");
	printf(PURPLE ">" RESET ": turn right\n");
	printf("\n");
}

static int	parse_args(t_data *data, char **argv)
{
	if (check_file(argv[1], true) == FAILURE)
		clean_exit(data, FAILURE);
	parse_data(argv[1], data);
	if (get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	if (DEBUG_MSG)
		debug_display_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (err_msg("", ERR_INPUT, 1));
	init_main(&data);
	if (parse_args(&data, argv) != 0)
		return (1);
	init_mlx(&data);
	init_textures(&data);
	print_controls();
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
