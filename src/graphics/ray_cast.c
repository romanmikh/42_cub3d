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
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;  // (int-rounded player pos - actial pos) * distance travelled in TOTAL (diagonal) to move 1 unit in x => distance travelled in total to get to the first vertical gridline
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
static void	perform_dda(t_data *data, t_ray *ray)// this one moves WHILE no hit, so projects the ray to the wall
{ // returns nothing, just updates our x and y positions of the ray to where it hits the wall
	int	hit;  // wall

	hit = 0;
	while (hit == 0) // at each square of map it checks distance to x and y, takes the shortest one, so wiggles in the right direction always
	{
		// total distance to get to horizontal edge line > to vertical, so:
		if (ray->sidedist_x < ray->sidedist_y)  // ray is moving more in X direction than in Y |gradient < 1|
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->hit_horiz_wall = 0;
		}
		else  // Move in Y direction
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->hit_horiz_wall = 1;
		}
		if (ray->map_y < 1
			|| ray->map_x < 1
			|| ray->map_y > data->map_data.height - 1
			|| ray->map_x > data->map_data.width - 2)
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')  // wall/edge = 1, so stop
			hit = 1;
	}
}

// Calculates the height of the wall and where to start and end drawing it.
static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	if (ray->hit_horiz_wall == 0) // if hits vertical wall (top down from map)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);  // PERPENDICULAR DIST. entire side_dist - tail deltadist 
	else  // exact perpendicular distance to wall (without initial delta)
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
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
