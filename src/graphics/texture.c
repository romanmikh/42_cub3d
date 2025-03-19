/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:54:03 by sbelcher          #+#    #+#             */
/*   Updated: 2025/03/19 19:54:05 by sbelcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	render_floor(data, ray, y, x);
}

void	render_floor(t_data *data, t_ray *ray, int y, int x)
{
	if (data->text_data.floort && data->text_data.ceilingt)
	{
		if (ray->hit_horiz_wall == 0 && ray->dir_x > 0)
		{
			data->floor_data.f_x_wall = ray->map_x;
			data->floor_data.f_y_wall = ray->map_y + ray->wall_hit_x_coord;
		}
		else if (ray->hit_horiz_wall == 0 && ray->dir_x < 0)
		{
			data->floor_data.f_x_wall = ray->map_x + 1.0;
			data->floor_data.f_y_wall = ray->map_y + ray->wall_hit_x_coord;
		}
		else if (ray->hit_horiz_wall == 1 && ray->dir_y > 0)
		{
			data->floor_data.f_x_wall = ray->map_x + ray->wall_hit_x_coord;
			data->floor_data.f_y_wall = ray->map_y;
		}
		else
		{
			data->floor_data.f_x_wall = ray->map_x + ray->wall_hit_x_coord;
			data->floor_data.f_y_wall = ray->map_y + 1.0;
		}
		y = ray->draw_end + 1;
		update_floor_pixels(data, ray, y, x);
	}
}

void	update_floor_pixels(t_data *data, t_ray *ray, int y, int x)
{
	t_floor_data	*f_d;

	f_d = &data->floor_data;
	while (y < data->win_height)
	{
		f_d->current_dist = (data->win_height) / (2.0 * y - data->win_height);
		f_d->weight = f_d->current_dist / ray->wall_dist;
		f_d->current_f_x = f_d->weight * f_d->f_x_wall + (1.0 - f_d->weight)
			* data->player.pos_x;
		f_d->current_f_y = f_d->weight * f_d->f_y_wall + (1.0 - f_d->weight)
			* data->player.pos_y;
		f_d->f_tex_x = (int)(f_d->current_f_x * (64.0)) % 64;
		f_d->f_tex_y = (int)(f_d->current_f_y * (64.0)) % 64;
		f_d->f_color = data->textures[FLOOR][(f_d->f_tex_y * 64)
			+ f_d->f_tex_x];
		f_d->c_color = data->textures[CEILING][(f_d->f_tex_y * 64)
			+ f_d->f_tex_x];
		data->texture_pixels[y - 1][x] = f_d->f_color;
		data->texture_pixels[data->win_height - y][x] = f_d->c_color;
		y++;
	}
	data->texture_pixels[data->win_height - y][x] = f_d->c_color;
}
