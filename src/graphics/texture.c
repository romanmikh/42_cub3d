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
	tex->x = (int)(ray->wall_x * tex->size);  // Calculate the x coordinate where ray hits texture
	if ((ray->hit_horiz_wall == 0 && ray->dir_x < 0) // flip texture horizontally if needed
		|| (ray->hit_horiz_wall == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height; // Calculate how much the texture should scale per pixel
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start; // Loop through every Y pixel in the column and apply the correct texture color
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1); // Get the texture Y coordinate
		tex->pos += tex->step; // Move to the next texture row
		colour = data->textures[tex->index][tex->size * tex->y + tex->x]; // Get the pixel color from the texture array
		if (tex->index == NORTH || tex->index == EAST) // Apply shading for depth effect (darken North and East walls)
			colour = (colour >> 1) & 8355711;
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
