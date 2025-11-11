/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:35:04 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/11 23:20:10 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"
# include <math.h>
# include <limits.h>

# define TEX_SIZE 128

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

void	raycasting(t_game *g);
void	draw_column(t_game *g, t_caster *s, t_img *back);

#endif
