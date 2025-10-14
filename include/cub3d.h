/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:01:53 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 14:37:33 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"
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
# define PLAYER_DIRECTIONS "NESW" // north east south west

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
} t_config;

typedef struct	s_player
{
	double	pos[2];
	int		angle;
} t_player;

// a map object, containing the string, the dimensions
typedef struct s_map
{
	char	**grid;
	int	size[2];
} t_map;

/* ************************************************************************** */
// WINDOW MANAGEMENT

typedef struct s_window {
  mlx_t *mlx;
  mlx_image_t *img;
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




int		init_window(t_window *window);
void	cleanup_window(t_window *window);
void	key_hook(mlx_key_data_t key_press, void *param);



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
int	parse_config_data(t_parse *parse, t_config *config, char *filename);

// check files exist, are valid etc.
int get_texture_files(void);

// check files exist, are valid etc.
int get_floor_ceiling_values(void);


// Reads <filename> into heap and:
// 	1) checks it exists
// 	1) checks is valid .cub file
// 	2) maximum bounds
int	create_map(t_map *map, char *raw_map_string);


// VALIDATION

// check that map is closed.
int		allocate_contiguous_map(char ***map, size_t cols, size_t rows);
void	find_player(char **map, double *player, int cols, int rows);
int		map_is_closed(t_map *map, double *player);
/* int	allocate_flat_map(t_map *map); */
int allocate_game_map(t_map *map, char *raw_map_string);


// DRAWING


// CLEANUP
void	cleanup_map(t_map *map);
void	cleanup_config(t_config *config);
void	cleanup_parse(t_parse *parse);

void	cleanup_all(t_game *game);


// viewport
int handle_direction(void);
int handle_rotation(void);

// movement
int handle_movement(void);

// not passing walls, checking if move is legal!
int bounds_managament(void);

// DEBUG
void	debug_map(t_map *map);

// basically prints a little report of all that we know.
void	debug_config(t_parse *parse, t_config *config, t_map *map);
#endif
