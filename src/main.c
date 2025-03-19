/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:10:17 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:10:25 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	render(&data);
	init_input_hooks(&data);
	mlx_loop_hook(data.mlx, move_and_render, &data);
	mlx_loop(data.mlx);
	return (0);
}
