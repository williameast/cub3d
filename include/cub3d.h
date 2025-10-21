/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:01:53 by weast             #+#    #+#             */
/*   Updated: 2025/10/21 21:51:22 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include "fcntl.h"

# define WIDTH 1024 // window width
# define HEIGHT 768 // window height

# define FILE_EXT ".cub" // file extension used.
# define WIN_NAME "cub3d_debug"

# define OK 0
# define ERR -1
# define INVALID -2

/* ************************************************************************** */
// MAPS

// I have macroed this, so we can add valid characters quickly.
// for player chars, it will only be valid with one and only one
// player character.
# define MAP_VALID_PLAYER_CHARS "NESW" // north east south west

// these can come up as many times as needed.
# define MAP_VALID_ENV_CHARS " \n01" // note the space.


/* ************************************************************************** */
// GRID SYSTEM

enum coordinates
{
	x,
	y,
};


/* ************************************************************************** */
// STRUCTURE DEFINITIONS

typedef struct s_parse
{
	char	*raw_file_string;
	char	*raw_map_string;
	char	*raw_col_floor;
	char	*raw_col_ceiling;
} t_parse;

// temp object. RGB
typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_ea;
	char	*tex_we;
	int		col_floor;
	int		col_ceiling;
}	t_config;

typedef struct s_texture
{
	char	*data;
	int		width;
	int		bpp;
	int		stride;
}	t_texture;

typedef struct s_player
{
	double	pos[2];
	int		angle;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		size[2];
}	t_map;

typedef struct s_draw
{
	int		wall_hight;
	int		px_wall_start;
	int		px_wall_end;
	double	wall_x_ratio;
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
}	t_draw;
/* ************************************************************************** */
// WINDOW MANAGEMENT

typedef struct s_window {
  void *mlx;
  void *win;
  void *img;
  char *img_data;
  int bits_per_pixel;
  int size_line;
  int endian;
  int width;
  int height;
} t_window;

typedef struct s_game
{
	t_player player;
	t_map	map;
	t_window win;
	t_config config;
	int	exit_code;
} t_game;

typedef struct s_axis
{
	double	player_dir;
	int		player_tile;
	double	player_offset;
	double	ray_dir;
	double	side_dist;
	double	delta_dist;
	int		step;
	double	plane;
}	t_axis;

typedef struct s_caster_state
{
	int		px_col_x;
	double	cam_x;
	int		wall_side;
	double	wall_dist;
	t_axis	x;
	t_axis	y;
}	t_caster;

int		init_window(t_window *window);
void	cleanup_window(t_window *window);
int		key_hook(int keycode, void *param);

/* ************************************************************************** */
// PARSING

// Line identifier enum for config parsing
typedef enum e_line_id
{
	LINE_NO,
	LINE_SO,
	LINE_WE,
	LINE_EA,
	LINE_F,
	LINE_C,
	LINE_MAP,
	LINE_EMPTY,
	LINE_INVALID
} t_line_id;


// capture all config info and map. passes a pointer to begnning
// of map object.
int			parse_config_data(t_parse *parse, t_config *config, char *filename);
int			increment_and_check(int *counter);
char		*extract_value(char *line, int skip);
t_line_id	return_line_identifier(char *line);
void		cleanup_parse(t_parse *parse);
int			return_offset(t_parse *parse);
int			check_config_is_valid(t_parse *parse);
int			store_config_values(t_parse *parse, t_config *config);

// check files exist, are valid etc.
int get_texture_files(void);

// check files exist, are valid etc.
int get_floor_ceiling_values(void);


// Reads <filename> into heap and:
// 	1) checks it exists
// 	1) checks is valid .cub file
// 	2) maximum bounds
int	create_map(t_map *map, char *raw_map_string, t_game *game);


// VALIDATION

// check that map is closed.
int		allocate_contiguous_map(char ***map, size_t cols, size_t rows);
void	find_player(char **map, double *player, int cols, int rows);
int		map_is_closed(t_map *map, double *player, t_game *game);
/* int	allocate_flat_map(t_map *map); */
int		allocate_game_map(t_map *map, char *raw_map_string);

// PARSING;
int	parse_map(t_game *game, char *filename);

// DRAWING


// CLEANUP
void	cleanup_all(t_game *game);


// viewport
int handle_direction(void);
int handle_rotation(void);

// movement
int handle_movement(void);

// not passing walls, checking if move is legal!
int bounds_managament(void);

// ERROR
int	handle_error(char *msg, t_game *game, int error);

// DEBUG
void	debug_map(t_map *map);

// basically prints a little report of all that we know.
void	debug_game(t_game *game);
#endif
