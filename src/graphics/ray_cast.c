/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:13:46 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:13:48 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/******************************************************************************
- decides whether to step left or right (x) and up or down (y)
- computes distances to first gridlines in x and y
- side_dist_x = distance to first vertical gridline
- = (int-rounded player pos - actual pos) * distance travelled in x per step
******************************************************************************/
static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) \
							* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) \
							* ray->delta_dist_y;
	}
}

/******************************************************************************
- moves the ray forward (incrementing 1 map square at a time) using DDA
- at each square of map check distance to x and y, takes the shortest one
- so wiggles in the right direction in a discrete grid, until it hits a wall
******************************************************************************/
static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->hit_horiz_wall = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->hit_horiz_wall = 1;
		}
		if (ray->map_y < 1
			|| ray->map_x < 1
			|| ray->map_y > data->map_data.height - 1
			|| ray->map_x > data->map_data.width - 2)
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

/******************************************************************************
- Calculates wall height and where to start and end drawing it on the screen
- line_height intuition: if small wall_dist -> large height because can see 
	much/all of the wall (0 dist = inf height)
- -floor(ray->wall_hit_x_coord) to get exact location on the tile hit 
	(no y coord because from player's POV & only need the x=ray=column pos)
******************************************************************************/
static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->hit_horiz_wall == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->hit_horiz_wall == 0)
		ray->wall_hit_x_coord = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_hit_x_coord = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_hit_x_coord -= floor(ray->wall_hit_x_coord);
}

/******************************************************************************
- goal: determine what the player sees
- shoot "rays" (vertical slices of the screen) from the player's position
- check where they hit walls, and draw vertical textured stripes on the screen

- x: current vertical column of screen
- set_dda(); determiene direction of ray's movement
- perform_dda(); project ray until it hits a wall
- calculate_line_height(); compute how tall the wall should be
******************************************************************************/
int	ray_cast(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < data->win_width)
	{
		init_ray_cast_info(x, &ray, player);
		set_dda(&ray, player);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, player);
		update_texture_pixels(data, &data->text_data, &ray, x);
		x++;
	}
	return (SUCCESS);
}
