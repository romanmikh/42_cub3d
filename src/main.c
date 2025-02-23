#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (err_msg("", ERR_INPUT, 1));
	init_main(&data);
	if (check_input(&data, argv) != 0)
		return (1);
	init_mlx(&data);
	init_textures(&data);
	launch_msg();
	render_images(&data);
	init_input_hooks(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
