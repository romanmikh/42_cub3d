#include "cub3d.h"

// Determines which texture to use based on which side of the wall was hit
static void	get_texture_index(t_data *data, t_ray *ray)
{
	if (ray->hit_horiz_wall == 0)
	{
		if (ray->dir_x < 0)
			data->text_data.index = WEST;
		else
			data->text_data.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->text_data.index = SOUTH;
		else
			data->text_data.index = NORTH;
	}
}

void	update_texture_pixels(t_data *data, t_text_data *tex, t_ray *ray, int x)
{
	int			y;
	int			colour;

	get_texture_index(data, ray);
	tex->x = (int)(ray->wall_hit_x_coord * tex->size);  // Calculate the x coordinate where ray hits texture
	if ((ray->hit_horiz_wall == 0 && ray->dir_x < 0) // flip texture horizontally if needed
		|| (ray->hit_horiz_wall == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->scale = 1.0 * tex->size / ray->line_height; // Calculate how much the texture should scale per pixel
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->scale; // starting vertical position IN THE TEXTURE, not the screen
	// so if whole texture fits on screen (daw_start >= 0), start (tex->pos) will be 0
	// if not whole texture fits, starting pos > 0
	// sub draw_start into pos to see this mathematically
	y = ray->draw_start; // Loop through every Y pixel in the column and apply the correct texture color
	while (y < ray->draw_end)
	{
		// & compares binary representations of two numbers and keeps only bits that are 1 in both numbers
		// => 1101 & 0101 = 0101
		// 13 & 7 = 5
		// if tex->pos = 130.8, int makes it 130. tex->size = 64, 128 etc
		// so tex->size-1 creates a "bitmask" that is used to wrap texture coords with 2^x bounds (modulo kind of)
		// 130 & 63 = 10000010 & 00111111 = 00000010 = 2
		// 2 is the wrapped amount
		// SAME AS tex->y = (int)tex->pos % (tex->size);
		tex->y = (int)tex->pos;// & (tex->size - 1); // Get the texture Y coordinate
		// we need to modulo because we don't wan tto look beyond the texture's bounds & cause leaks
		tex->pos += tex->scale; // Move to the next texture row
		colour = data->textures[tex->index][tex->size * tex->y + tex->x]; // Get the pixel color from the texture array
		if (colour > 0) // Store the final color in the frame buffer if it's not transparent
			data->texture_pixels[y][x] = colour;
		y++;
	}
}

void	set_image_pixel(t_img *image, int x, int y, int colour)
{
	int	pixel;
	// Multiply by y becayse image is stored in a 1D array, but we treat it as a 2D grid
	pixel = y * (image->size_line / 4) + x;  // Calculate the pixel's position in the image buffer
	image->addr[pixel] = colour;   // Assign the color to the pixel
}
