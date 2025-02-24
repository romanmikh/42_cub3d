#ifndef CUB3D_H
# define CUB3D_H

// Includes 
# include "mlx.h"
# include "inc/libft.h"

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <X11/X.h>
# include <string.h>
# include <X11/keysym.h>

// Macros
# define TEX_SIZE 64
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960
# define STEP_SIZE 0.015
# define ROTATION_ANGLE 0.015

// Enumerations
enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};
// Enumerations
enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

// Error messages
# define ERR_INVALID_MAP "Invalid map"
# define ERR_MAP_MISSING "Map data missing"
# define ERR_MLX_START "Failed to start mlx"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_TEX_RGB_VAL "RGB value is invalid"
# define ERR_TEX_MISSING "Texture files missing"
# define ERR_TEX_INVALID "Texture files invalid"
# define ERR_MLX_IMG "Failed to create mlx image"
# define ERR_MLX_WIN "Failed to create mlx window"
# define ERR_COLOUR_MISSING "Colour values missing"
# define ERR_PLAYER_POS "Invalid player start position"
# define ERR_MAP_TOO_SMALL "Map must be larger than 3x3"
# define ERR_MAP_LAST "Map must be last section in file"
# define ERR_MAP_NO_WALLS "Map must be fully enclosed by walls"
# define ERR_FILE_FORMAT ".cub and.xmp file extensions required"
# define ERR_PLAYER_DIR "Player direction must be N, S, E, or W"
# define ERR_INPUT "Required input format: ./cub3d ./maps/nature.cub"
# define ERR_FLOOR_CEILING "Floor and/or ceiling RGB colours are invalid"
# define ERR_NUM_PLAYER "Only one starting player location in map supported"
# define ERR_INV_LETTER "Invalid character in map. {0, 1, N, S, E, W} supported."

// Structures
typedef struct s_map_data
{
	int			fd;  // of .cub file
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			end_of_map_line_index; // 	Marks end of the map in the file
}	t_map_data;

typedef struct s_text_data
{
	char			*north;  // paths
	char			*south;
	char			*west;
	char			*east;
	int				*floor; // colours in RGB
	int				*ceiling;
	unsigned long	hex_floor;  // hex colour for mlx_pixel_put
	unsigned long	hex_ceiling;
	int				size; // texture resolution
	int				index; // which texture 
	double			step; // how much texture moves per pixel
	double			pos; // tracks vertical texture position
	int				x; // pixel coordinates on the texture 
	int				y;
}	t_text_data;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;  // bytes per row of image
	int		endian; // byte order of pixels
}	t_img;

typedef struct s_ray
{
	double	camera_x;  // x position of ray in camera space
	double	dir_x;
	double	dir_y;
	int		map_x;  // coorinates of ray
	int		map_y;
	int		step_x; // step direction for DDA
	int		step_y;
	double	sidedist_x; // dist to next grid line
	double	sidedist_y;
	double	deltadist_x; // step size
	double	deltadist_y;
	double	wall_dist; 
	double	wall_x; // x-coord of wall hit
	int		side; // 0 = N/S, 1 = E/W / indicates if ray hits vertical or horizontal wall
	int		line_height; // height of wall to draw
	int		draw_start; 
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir; // N, S, E, W at start
	double	pos_x; 
	double	pos_y;
	double	dir_x; 
	double	dir_y;
	double	plane_x; // camera plane for perspective
	double	plane_y;
	int		has_moved;
	int		move_x; // (-1, 0 1)
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_data
{
	void		*mlx;  // main mlx struct
	void		*win; // MLX window pointer
	int			win_height; 
	int			win_width;
	t_map_data	map_data;
	char		**map; // 2D map array
	t_player	player;
	t_ray		ray;
	int			**texture_pixels; // 2D buffer array of texture pixels
	int			**textures; // loaded texture data
	t_text_data	text_data;
}	t_data;

// Function prototypes
void	launch_msg();
int		check_input(t_data *data, char **argv);
int		create_map(t_data *data, char **map, int i);
int		is_valid_texture(t_data *data, t_text_data *textures);
int		is_valid_map(t_data *data, char **map_arr);
int		is_valid_map_borders(t_map_data *map, char **map_arr);
size_t	max_line_width(t_map_data *map, int i);
int		move_and_render(t_data *data);
void	render(t_data *data);
int		ray_cast(t_player *player, t_data *data);
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_text_data *tex, t_ray *ray, int x);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	init_input_hooks(t_data *data);
void	init_player_direction(t_data *data);
int		validate_move(t_data *data, double new_x, double new_y);
int		move_player(t_data *data);
int		rotate_player(t_data *data, double rot_dir);
void	graceful_exit(t_data *data, int code);
int		handle_exit(t_data *data);
int		free_data(t_data *data);
int		err_msg(char *detail, char *str, int code);
int		err_msg_val(int detail, char *str, int code);
void	init_main(t_data *data);
void	init_ray(t_ray *ray);
void	init_ray_cast_info(int x, t_ray *ray, t_player *player);
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	init_textures(t_data *data);
void	init_text_data(t_text_data *textures);
int		is_valid_file(char *arg, bool cub);
void	parse_input(char *path, t_data *data);
int		process_cub_file(t_data *data, char **map);
int		set_ceiling_floor_colours(t_data *data, t_text_data *textures,
			char *line, int j);

#endif
