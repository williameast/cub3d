/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:01:53 by weast             #+#    #+#             */
/*   Updated: 2025/11/14 12:04:28 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <X11/X.h>
# include "mlx.h"
# include "fcntl.h"

# define WIDTH 1024 // window width
# define HEIGHT 768 // window height

# define FILE_EXT ".cub" // file extension used.
# define WIN_NAME "cub3d"

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
# define MAP_VALID_ENV_CHARS " \n01D" // note the space.

# define VELOCITY 0.03

# define MAX_SMOKE_PARTICLES 50
/* ************************************************************************** */
// GRID SYSTEM

enum e_coordinates
{
	x,
	y,
};

/* ************************************************************************** */
// INPUT KEYS

typedef enum e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_X,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ESCAPE,
	KEY_COUNT,
	KEY_INVALID = -1
}	t_key;

/* ************************************************************************** */
// STRUCTURE DEFINITIONS

typedef struct s_parse
{
	char	*raw_file_string;
	char	*raw_map_string;
	char	*raw_col_floor;
	char	*raw_col_ceiling;
}	t_parse;

typedef enum e_directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_dir;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		bytespp;
	int		size_line;
	int		endian;
}	t_img;

// temp object. RGB
typedef struct s_config
{
	char	*tex_path[4];
	t_img	tex[4];
	int		col_floor;
	int		col_ceiling;
}	t_config;

/* ************************************************************************** */
// WINDOW MANAGEMENT

typedef struct s_render_state
{
	void	*mlx;
	int		width;
	int		height;
	void	*win;
	t_img	*front;
	t_img	*back;
	t_img	frames[2];
	int		key_state[KEY_COUNT];
}	t_render;

typedef struct s_player
{
	double	pos[2];
	float	angle;
	float	dir[2];
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		size[2];
}	t_map;


typedef struct s_smoke_particle
{
	float	pos[2];
	float	velocity[2];
	int		size;
	int		color;
	float	lifetime;
	int		active;
}	t_smoke;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_render	render;
	t_config	config;
	t_smoke		smoke[MAX_SMOKE_PARTICLES];
	int			exit_code;
}	t_game;

int		render_frame(void *arg);
int		init_window(t_game *g, t_render *r);
int		key_hook(int keycode, void *param);

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
void	cleanup_all(t_game *g, t_render *r);
int		perror_and_clean(char *err_str, t_game *g);


// viewport
int handle_direction(void);
int handle_rotation(void);

// movement
int handle_keypress(int keycode, void *param);
int handle_keyrelease(int keycode, void *param);
void	move(t_game *game);
t_key	keycode_to_key(int keycode);

// not passing walls, checking if move is legal!
int bounds_managament(void);

// ERROR
int	handle_error(char *msg, t_game *game, int error);
int	clean_exit(void *params);
// MINIMAP
void	draw_minimap(t_game *game);
// SMOKE
void	spawn_smoke(t_game *game, int origin[2]);
void	update_smoke(t_game *game);
void	draw_smoke(t_game *game);
void	init_smoke(t_game *game);
// DEBUG
void	debug_map(t_map *map);
void	put_square(t_img *img, int point[2] , int size, int colour);
void	calculate_walk(float dir[2], float *new_x, float *new_y, int sign);
void	calculate_strafe(float dir[2], float *new_x, float *new_y, int sign);

// basically prints a little report of all that we know.
void	debug_game(t_game *game);

#endif
