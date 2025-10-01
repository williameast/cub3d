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


typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
}	t_window;

int		init_window(t_window *window);
void	cleanup_window(t_window *window);
void	key_hook(mlx_key_data_t key_press, void *param);


// exit.c



#endif
