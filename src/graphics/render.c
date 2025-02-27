#include "cub3d.h"

// convert 2D array to 1D row for MLX (RGBA (Alpha=transarency) -> /4 not /3)
static void	set_image_pixel(t_img *image, int x, int y, int colour)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;  // Calculate the pixel's position in the image buffer
	image->addr[pixel] = colour;   // Assign the color to the pixel
}

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);  // first draw textures
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->text_data.hex_ceiling);  // draw ceiling
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->text_data.hex_floor);  // draw floor
}


static void	render_frame(t_data *data)
{
	t_img	image;  // Image buffer
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height) // Loop through every pixel in the window
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);  // Set pixel color
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

void	render(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray); // Reset the ray structure
	ray_cast(&data->player, data); // Project all rays till they hit a wall, get hit coords, and calculate wall height and texture
	render_frame(data); // Draw the computed frame to the window
}

// goal: update frame when player moves & display in 3D
// game state exists in memory, this visualises it
int	move_and_render(t_data *data)
{
	data->player.has_moved += move_player(data);
	if (data->player.has_moved == 0)  // if player hasn't moved, do nothing
		return (0);
	render(data);
	return (0);
}
