#include "cub3d.h"

static int	key_press_event(int key, t_data *data)
{
	if (key == XK_Escape)
		handle_exit(data);
	if (key == XK_a)
		data->player.move_x = -1;
	if (key == XK_d)
		data->player.move_x = 1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_w)
		data->player.move_y = 1;
	if (key == XK_Left)
		data->player.rot_dir -= 1;
	if (key == XK_Right)
		data->player.rot_dir += 1;
	return (0);
}

static int	key_release_event(int key, t_data *data)
{
	if (key == XK_Escape)
		handle_exit(data);
	if (key == XK_a && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == XK_d && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == XK_w && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == XK_s && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == XK_Left && data->player.rot_dir <= 1)
		data->player.rot_dir = 0;
	if (key == XK_Right && data->player.rot_dir >= -1)
		data->player.rot_dir = 0;
	return (0);
}

void	init_input_hooks(t_data *data)
{
	mlx_hook(data->win, ClientMessage, NoEventMask, handle_exit, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_event, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_event, data);
}
