#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "fcntl.h"

# define OK 0
# define ERR -1
# define WIDTH 1024 // window width
# define HEIGHT 768 // window height

#define FILE_EXT ".cub" // file extension used.

# define WIN_NAME "cub3d_debug"

// DM main configuration
/* typedef struct s_config; */


// a single coordinate point.
typedef struct s_2D {
  int x;
  int y;
} t_2D;

// a map object, containing the string, the dimensions
typedef struct s_map
{
	char	*raw_map_string;
	t_2D	dimension;
} t_map;


// a window object.
typedef struct s_window {
  mlx_t *mlx;
  mlx_image_t *img;
  int width;
  int height;
} t_window;


int		init_window(t_window *window);
void	cleanup_window(t_window *window);
void	key_hook(mlx_key_data_t key_press, void *param);



// PARSING

// check .cub file format, is readable and present
int check_file_format(void);

// check files exist, are valid etc.
int get_texture_files(void);

// check files exist, are valid etc.
int get_floor_ceiling_values(void);

int	get_map_max_dimensions(t_map *map);

// use gnl to extract char data of map
int	read_map_as_string(t_map *map, char *filename);

// basically, we only need to add spaces at the end of each line to equal MAX_WIDTH.
int	map_normalizer(void);

// read in the normalized 1d char map data, and fill in the array.
int create_array(void);

// VALIDATION

// check that map is closed.
int	allocate_contiguous_map(char ***map, size_t cols, size_t rows);
int	map_is_closed(char ***map, size_t cols, size_t rows);


// DRAWING


// CLEANUP
int	cleanup_map(t_map *map);


// viewport
int handle_direction(void);
int handle_rotation(void);

// movement
int handle_movement(void);

// not passing walls, checking if move is legal!
int bounds_managament(void);

// DEBUG
void	debug_2D(t_2D point);


#endif
