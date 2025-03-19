#include "cub3d.h"

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

/******************************************************************************
- tex->x: calculate the x coordinate where ray hits texture
- tex_scale: calculate how much the texture should scale per screen pixel

- tex->pos = starting vertical position IN THE TEXTURE, not on the screen
- so if whole texture fits on screen (i.e. draw_start >= 0), start (tex->pos) 
- will be 0. If not whole texture fits, tex->pos > 0
- substitute the equation for draw_start into tex->pos to see this mathematically
******************************************************************************/
void	update_texture_pixels(t_data *data, t_text_data *tex, t_ray *ray, int x)
{
	int			y;
	int			colour;

	get_texture_index(data, ray);
	tex->x = (int)(ray->wall_hit_x_coord * tex->size);
	if ((ray->hit_horiz_wall == 0 && ray->dir_x < 0)
		|| (ray->hit_horiz_wall == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->scale = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->scale;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos;
		tex->pos += tex->scale;
		colour = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (colour > 0)
			data->texture_pixels[y][x] = colour;
		y++;
	}

	// ========== FLOOR & CEILING CASTING ==========

	// Determine the floor point at the bottom of the wall based on direction
	if (ray->hit_horiz_wall == 0 && ray->dir_x > 0) // East wall
	{
		data->floor_data.floorXWall = ray->map_x;
		data->floor_data.floorYWall = ray->map_y + ray->wall_hit_x_coord;
	}
	else if (ray->hit_horiz_wall == 0 && ray->dir_x < 0) // West wall
	{
		data->floor_data.floorXWall = ray->map_x + 1.0;
		data->floor_data.floorYWall = ray->map_y + ray->wall_hit_x_coord;
	}
	else if (ray->hit_horiz_wall == 1 && ray->dir_y > 0) // South wall
	{
		data->floor_data.floorXWall = ray->map_x + ray->wall_hit_x_coord;
		data->floor_data.floorYWall = ray->map_y;
	}
	else // North wall
	{
		data->floor_data.floorXWall = ray->map_x + ray->wall_hit_x_coord;
		data->floor_data.floorYWall = ray->map_y + 1.0;
	}

	y = ray->draw_end;
while (y < data->win_height)
{
    // Compute distance of this row from player
    data->floor_data.currentDist = (data->win_height) / (2.0 * y - data->win_height);
    // Compute weight for interpolation
    data->floor_data.weight = data->floor_data.currentDist / ray->wall_dist;
    // Compute actual floor and ceiling world positions
    data->floor_data.currentFloorX = data->floor_data.weight * data->floor_data.floorXWall + (1.0 - data->floor_data.weight) * data->player.pos_x;
    data->floor_data.currentFloorY = data->floor_data.weight * data->floor_data.floorYWall + (1.0 - data->floor_data.weight) * data->player.pos_y;
     // Scale world coordinates to texture space
	data->floor_data.floorTexX = (int)(data->floor_data.currentFloorX * (64.0)) % 64;
    data->floor_data.floorTexY = (int)(data->floor_data.currentFloorY * (64.0)) % 64;
    // Sample colors from textures
    data->floor_data.floorColor = data->textures[FLOOR][(data->floor_data.floorTexY * 64) + data->floor_data.floorTexX];
    data->floor_data.ceilingColor = data->textures[CEILING][(data->floor_data.floorTexY * 64) + data->floor_data.floorTexX];
     // Set pixel colors
     data->texture_pixels[y][x] = data->floor_data.floorColor;           // Floor
     data->texture_pixels[data->win_height - y][x] = data->floor_data.ceilingColor;  // Ceiling (mirrored)
	 y++;
}
}
