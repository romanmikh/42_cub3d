#include "cub3d.h"

// Decides whether to step left or right (x) and up or down (y)
// Computes distances to firs gridlines in x and y
static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)  // ray moving left
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;  // (int-rounded player pos - actual pos) * distance travelled in x per diagonal step = total distance to first vertical gridline
	}
	else  // ray moving right
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0) // ray moving up
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else // ray moving down
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

// Moves the ray forward (incrementing 1 map square at a time) using the DDA algorithm
// updates ray->map_x/_y until it hits a wall, so gives us the exact x and y coordinates of the wall hit
static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0) // at each square of map it checks distance to x and y, takes the shortest one, so wiggles in the right direction in a discrete grid
	{
		if (ray->side_dist_x < ray->side_dist_y)  // = total distance to get to horizontal edge line > to vertical edge, so ray goes horizontally first
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->hit_horiz_wall = 0;
		}
		else  // move vertically
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->hit_horiz_wall = 1;
		}
		if (ray->map_y < 1
			|| ray->map_x < 1
			|| ray->map_y > data->map_data.height - 1
			|| ray->map_x > data->map_data.width - 2)  // outside of map
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')  // wall/edge = 1, so stop
			hit = 1;
	}
}

// Calculates the height of the wall and where to start and end drawing it on the screen
static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->hit_horiz_wall == 0) // if hits vertical wall (from top down POV)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);  // entire side_dist travelled - tail deltadist = perpendicular distance to the wall
	else  // exact perpendicular distance to wall (without initial delta)
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);  // small dist -> large height. 0 dist = inf height
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2; // center start with win_height
	if (ray->draw_start < 0)
		ray->draw_start = 0; // edge cases
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->hit_horiz_wall == 0)  // if vertical wall (top down view)
		ray->wall_hit_x_coord = player->pos_y + ray->wall_dist * ray->dir_y; // get exact x coordinate of wall hit. pos_y + #units in x * y stpe size per unit x
	else // if horizontal wall
		ray->wall_hit_x_coord = player->pos_x + ray->wall_dist * ray->dir_x; // get exact y coordinate of wall hit
	ray->wall_hit_x_coord -= floor(ray->wall_hit_x_coord); // modulo to get exact location on exactly that tile only
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
	t_ray	ray;
	int		x;  // current vertical column of screen

	x = 0;
	ray = data->ray;
	while (x < data->win_width)  // Loop through every column on screen from left to right
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
