#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"

# define WIDTH 1024
# define HEIGHT 768

# define WIN_NAME "cub3d_debug"

typedef struct s_window {
  mlx_t *mlx;
  mlx_image_t *img;
  int width;
  int height;
} t_window;

int		init_window(t_window *window);
void	cleanup_window(t_window *window);
void	key_hook(mlx_key_data_t key_press, void *param);



// parsing

// check .cub file format, is readable and present
int check_file_format(void);

// check files exist, are valid etc.
int get_texture_files(void);

// check files exist, are valid etc.
int get_floor_ceiling_values(void);

int	get_map_max_dimensions(void);

// use gnl to extract char data of map
int read_map_data_as_char(void);

// basically, we only need to add spaces at the end of each line to equal MAX_WIDTH.
int	map_normalizer(void);

// read in the normalized 1d char map data, and fill in the array.
int create_array(void);

#endif
