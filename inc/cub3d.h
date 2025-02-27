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
# define WIN_WIDTH 600
# define WIN_HEIGHT 450
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

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

// Error messages
# define ERR_MAP_INVALID "Invalid map"
# define ERR_MAP_MISSING "Map data missing"
# define ERR_MLX_START "Failed to start mlx"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_TEX_RGB_VAL "RGB value is invalid"
# define ERR_TEX_MISSING "Texture files missing"
# define ERR_TEX_INVALID "Texture files invalid"
# define ERR_MLX_IMG "Failed to create mlx image"
# define ERR_MLX_WIN "Failed to create mlx window"
# define ERR_FILE_MISSING "No such file or directory"
# define ERR_RGB_COLOUR_MISSING "Colour values missing"
# define ERR_PLAYER_POS "Invalid player start position"
# define ERR_MAP_TOO_SMALL "Map must be larger than 3x3"
# define ERR_MAP_TRAIL "Map must be last section in file"
# define ERR_MAP_BORDERS "Map must be fully enclosed by walls"
# define ERR_FILE_FORMAT ".cub and.xmp file extensions required"
# define ERR_PLAYER_DIR "Player direction must be N, S, E, or W"
# define ERR_INPUT "Required input format: ./cub3d ./maps/nature.cub"
# define ERR_FLOOR_CEILING "Floor and/or ceiling RGB colours are invalid"
# define ERR_NUM_PLAYERS "Only one starting player location in map supported"
# define ERR_MAP_CHAR "Invalid character in map. {0, 1, N, S, E, W} supported."

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
	char			*north;  // paths to textures
	char			*south;
	char			*west;
	char			*east;
	int				*floor; // RGB colours
	int				*ceiling;
	unsigned long	hex_floor;  // hex RGB colours for mlx
	unsigned long	hex_ceiling;
	int				size; // texture resolution
	int				index; // which texture 
	double			scale; // how much texture to use per pixel
	double			pos; // where tex starts (starting from top of screen)
	int				x; // pixel coordinates on the texture 
	int				y;
}	t_text_data;

typedef struct s_img
{
	void	*img;  // image buffer
	int		*addr;
	int		bits_per_pixel;
	int		size_line;  // bytes per row of image
	int		endian; // byte order of pixels
}	t_img;

typedef struct s_ray
{
	double	field_of_view;  // all columns of screen. Left -> -1, right -> +1
	int		map_x;  // coorinates of ray
	int		map_y;
	double	dir_x;  // horiz/vert fractional step ray takes during DDA
	double	dir_y;
	int		step_x; // horiz/vert unit step ray takes during DDA
	int		step_y;
	double	side_dist_x; // dist to next grid line
	double	side_dist_y;
	double	delta_dist_x; // step size
	double	delta_dist_y;
	double	wall_dist; 
	double	wall_hit_x_coord; // x-coord of wall hit on texture
	int		hit_horiz_wall; // whether ray hits vert/horiz wall -> 0 = vert, 1 = horiz
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
	double	plane_x; // half of field of view, affected by rotations only
	double	plane_y;
	int		has_moved;
	int		move_x; // (-1, 0 1)
	int		move_y;
	int		rot_dir;
}	t_player;

typedef struct s_data
{
	void		*mlx;  // main mlx struct
	void		*win; // MLX window pointer
	int			win_height; 
	int			win_width;
	char		**map; // 2D map array
	int			**texture_pixels; // 2D buffer array
	int			**textures; // loaded texture data
	t_ray		ray;
	t_player	player;
	t_map_data	map_data;
	t_text_data	text_data;
}	t_data;

// Function prototypes
void	launch_msg();
void	render(t_data *data);
void	init_ray(t_ray *ray);
void	init_mlx(t_data *data);
int		free_data(t_data *data);
void	init_main(t_data *data);
int		move_player(t_data *data);
int		handle_exit(t_data *data);
void	init_textures(t_data *data);
int		move_and_render(t_data *data);
void	init_input_hooks(t_data *data);
void	init_texture_pixels(t_data *data);
int		is_valid_file(char *arg, bool cub);
void	init_player_direction(t_data *data);
void	graceful_exit(t_data *data, int code);
void	init_text_data(t_text_data *textures);
void	parse_input(char *path, t_data *data);
int		check_input(t_data *data, char **argv);
size_t	max_line_width(t_map_data *map, int i);
int		ray_cast(t_player *player, t_data *data);
int		is_valid_map(t_data *data, char **map_arr);
int		err_msg(char *detail, char *str, int code);
int		process_cub_file(t_data *data, char **map);
int		create_map(t_data *data, char **map, int i);
int		rotate_player(t_data *data, double rot_dir);
int		err_msg_val(int detail, char *str, int code);
int		is_valid_texture(t_data *data, t_text_data *textures);
int		is_valid_map_borders(t_map_data *map, char **map_arr);
int		is_valid_move(t_data *data, double new_x, double new_y);
void	init_ray_cast_info(int x, t_ray *ray, t_player *player);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	init_img(t_data *data, t_img *image, int width, int height);
void	update_texture_pixels(t_data *data, t_text_data *tex, t_ray *ray, int x);
int		set_ceiling_floor_colours(t_data *data, t_text_data *textures,
			char *line, int j);

#endif
