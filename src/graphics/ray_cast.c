#include "cub3d.h"

/*
- We are doing the initial set up for the dda
- dda algorithm will jump one square in each loop eiter in a x or y direction
- ray->sidedist_x or y = distance from the ray start position to the
	next x or y position
- if x or y < 0 go the next x or y to the left
- if x or y > 0 go the next x or y to the right
*/

// Determines whether to step left or right (x) and up or down (y).
// Computes the initial side distances for stepping.
static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)  // ray moving left
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else  // ray moving right
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0) // ray moving up
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else // ray moving down
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

/*
- We implement the DDA algorithm -> the loop will increment 1 square 
-   until we hit a wall
- If the sidedistx < sidedisty, x is the closest point from the ray
*/
// Moves the ray forward through the grid using the DDA algorithm.
static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;  // wall

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)  // Move in X direction
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else  // Move in Y direction
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > data->map_data.height - 0.25  // why 0.25?
			|| ray->map_x > data->map_data.width - 1.25)  // why 1.25?
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')  // wall/edge = 1, so stop
			hit = 1;
	}
}

// Calculates the height of the wall and where to start and end drawing it.
static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

// goal: determine what the player sees

// in a 3D first-person view by using raycasting
// shoot "rays" from the player's position in different directions, check where they hit walls, and use this to draw vertical stripes on the screen
// each ray represents a single vertical slice of the screen 
// casts multiple rays (one per column of pixels) to render the full view
// Moves the ray through the grid using DDA (Digital Differential Analysis)
// tops when the ray hits a wall and calculates the correct height for that column
// Stores the wall height and texture to render the final 3D image
int	ray_cast(t_player *player, t_data *data)
{
	t_ray	ray; // stores raycasting details
	int		x;  // current vertical column of screen

	x = 0;
	ray = data->ray;
	while (x < data->win_width)  // Loop through every vertical screen column from left to right
	{
		init_ray_cast_info(x, &ray, player);
		set_dda(&ray, player); // determien direction of ray's movement
		perform_dda(data, &ray); // detect wall collisions (from above?)
		calculate_line_height(&ray, data, player); // Compute how tall the wall should be
		update_texture_pixels(data, &data->text_data, &ray, x);
		x++;
	}
	return (SUCCESS);
}
