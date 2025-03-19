/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:12:48 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:12:49 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_player_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_y * STEP_SIZE;
	new_y = data->player.pos_y - data->player.dir_x * STEP_SIZE;
	return (is_valid_move(data, new_x, new_y));
}

static int	move_player_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_y * STEP_SIZE;
	new_y = data->player.pos_y + data->player.dir_x * STEP_SIZE;
	return (is_valid_move(data, new_x, new_y));
}

static int	move_player_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * STEP_SIZE;
	new_y = data->player.pos_y + data->player.dir_y * STEP_SIZE;
	return (is_valid_move(data, new_x, new_y));
}

static int	move_player_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * STEP_SIZE;
	new_y = data->player.pos_y - data->player.dir_y * STEP_SIZE;
	return (is_valid_move(data, new_x, new_y));
}

int	move_player(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.move_y == 1)
		moved += move_player_forward(data);
	if (data->player.move_y == -1)
		moved += move_player_backward(data);
	if (data->player.move_x == -1)
		moved += move_player_left(data);
	if (data->player.move_x == 1)
		moved += move_player_right(data);
	if (data->player.rot_dir != 0)
		moved += rotate_player(data, data->player.rot_dir);
	return (moved);
}
