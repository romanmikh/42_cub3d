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
}
