/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmikhayl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:09:53 by rmikhayl          #+#    #+#             */
/*   Updated: 2025/03/19 20:09:58 by rmikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define STEP_SIZE 0.005
# define ROTATION_ANGLE 0.005

// Enumerations
enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	FLOOR = 4,
	CEILING = 5
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
# define ERR_FLOOR_CEILING "Floor and/or ceiling RGB colours are invalid"
# define ERR_INPUT "Required input format: ./cub3D ./maps/pass/corridors.cub"
# define ERR_NUM_PLAYERS "Only one starting player location in map supported"
# define ERR_MAP_CHAR "Invalid character in map. {0, 1, N, S, E, W} supported."

// Structures
typedef struct s_map_data
{
	int			fd;
	char		*path;
	int			width;
	char		**file;
	int			height;
	int			line_count;
	int			end_of_map_line_index;
}	t_map_data;

typedef struct s_floor_data
{
	double	f_x_wall;
	double	f_y_wall;
	double	current_dist;
	int		f_color;
	int		c_color;
	double	weight;
	double	current_f_x;
	double	current_f_y;
	int		f_tex_x;
	int		f_tex_y;
}	t_floor_data;

typedef struct s_text_data
{
	int				x;
	int				y;
	double			pos;
	int				size;
	char			*west;
	char			*east;
	char			*floort;
	char			*ceilingt;
	int				index;
	double			scale;
	char			*north;
	char			*south;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
}	t_text_data;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		endian;
	int		size_line;
	int		bits_per_pixel;
}	t_img;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	int		step_x;
	int		step_y;
	int		draw_end;
	double	wall_dist;
	int		draw_start;
	int		line_height;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	field_of_view;
	int		hit_horiz_wall;
	double	wall_hit_x_coord;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		move_x;
	int		move_y;
	int		rot_dir;
	double	plane_x;
	double	plane_y;
	int		has_moved;
}	t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**map;
	int				win_width;
	int				**textures;
	int				win_height;
	int				**texture_pixels;
	t_ray			ray;
	t_player		player;
	t_map_data		map_data;
	t_text_data		text_data;
	t_floor_data	floor_data;	
}	t_data;

// Function prototypes
void	launch_msg(void);
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
void	init_floor_data(t_floor_data *floor);
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
void	render_floor(t_data *data, t_ray *ray, int y, int x);
int		is_valid_texture(t_data *data, t_text_data *textures);
int		is_valid_map_borders(t_map_data *map, char **map_arr);
int		is_valid_move(t_data *data, double new_x, double new_y);
void	init_ray_cast_info(int x, t_ray *ray, t_player *player);
void	init_texture_img(t_data *data, t_img *image, char *path);
void	init_img(t_data *data, t_img *image, int width, int height);
void	update_floor_pixels(t_data *data, t_ray *ray, int y, int x);
void	update_texture_pixels(t_data *data, t_text_data *tex, t_ray *ray, \
			int x);
int		set_ceiling_floor(t_data *data, t_text_data *textures,
			char *line, int j);

#endif
