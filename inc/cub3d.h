#ifndef CUB3D_H
# define CUB3D_H

# include "colors.h"
# include "inc/libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

// Macros
# ifndef DEBUG_MSG
#  define DEBUG_MSG 0
# endif

# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.015
# define ROTSPEED 0.015

// Error messages
# define ERR_INPUT "Required input format: ./cub3d maps/nature.cub"
# define ERR_FILE_FORMAT ".cub or.xmp file required"
# define ERR_FLOOR_CEILING "Floor and/or ceiling RGB colours are invalid"
# define ERR_INVALID_MAP "Invalid map"
# define ERR_INV_LETTER "Invalid character in map"
# define ERR_NUM_PLAYER "Only one starting player location in map supported"
# define ERR_TEX_RGB_VAL "Invalid RGB value"
# define ERR_TEX_MISSING "Missing textures"
# define ERR_TEX_INVALID "Invalid textures"
# define ERR_COLOR_MISSING "Missing colours"
# define ERR_MAP_MISSING "Missing map"
# define ERR_MAP_TOO_SMALL "Map must be > 3x3"
# define ERR_MAP_NO_WALLS "Ensure map is surrounded by 1s"
# define ERR_MAP_LAST "Map is not the last element in file"
# define ERR_PLAYER_POS "Invalid starting player position in map"
# define ERR_PLAYER_DIR "Map requires player position (N, S, E or W)"
# define ERR_MALLOC "Could not allocate memory"
# define ERR_MLX_START "Could not start mlx"
# define ERR_MLX_WIN "Could not create mlx window"
# define ERR_MLX_IMG "Could not create mlx image"

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

// Structures
typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;  // hex necessary for mlx_pixel_put
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_mapinfo	mapinfo;
	char		**map;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
}	t_data;

/* init/init_main.c */
void	init_main(t_data *data);
void	init_img_clean(t_img *img);
void	init_ray(t_ray *ray);

/* init/init_mlx.c */
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);

/* init/init_textures.c */
void	init_textures(t_data *data);
void	init_texinfo(t_texinfo *textures);

/* parsing/check_args.c */
int		check_file(char *arg, bool cub);

/* parsing/parse_data.c */
void	parse_data(char *path, t_data *data);

/* parsing/get_file_data.c */
int		get_file_data(t_data *data, char **map);

/* parsing/fill_color_textures.c */
int		fill_color_textures(t_data *data, t_texinfo *textures,
			char *line, int j);

/* parsing/create_game_map.c */
int		create_map(t_data *data, char **map, int i);

/* parsing/check_textures.c */
int		check_textures_validity(t_data *data, t_texinfo *textures);

/* parsing/check_map.c */
int		check_map_validity(t_data *data, char **map_tab);

/* parsing/check_map_borders.c */
int		check_map_sides(t_mapinfo *map, char **map_tab);

/* parsing/parsing_utils.c */
int		is_a_white_space(char c);
size_t	find_biggest_len(t_mapinfo *map, int i);

/* render/render.c */
int		render(t_data *data);
void	render_images(t_data *data);

/* render/raycasting.c */
int		raycasting(t_player *player, t_data *data);

/* render/texture.c */
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);

/* render/image_utils.c */
void	set_image_pixel(t_img *image, int x, int y, int color);

/* movement/input_handler.c */
void	listen_for_input(t_data *data);

/* movement/player_dir.c */
void	init_player_direction(t_data *data);

/* movement/player_pos.c */
int		validate_move(t_data *data, double new_x, double new_y);

/* movement/player_move.c */
int		move_player(t_data *data);

/* movement/player_rotate.c */
int		rotate_player(t_data *data, double rotdir);

/* exit/exit.c */
void	clean_exit(t_data *data, int code);
int		quit_cub3d(t_data *data);

/* exit/free_data.c */
void	free_tab(void **tab);
int		free_data(t_data *data);

/* error.c */
int		err_msg(char *detail, char *str, int code);
int		err_msg_val(int detail, char *str, int code);

/* debug/debug.c */
void	debug_display_data(t_data *data);
void	debug_display_player(t_data *data);
void	debug_print_char_tab(char **tab);

#endif
