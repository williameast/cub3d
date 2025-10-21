/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:28:45 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/21 13:33:35 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

/* RAYCASTING - Variables 
*
* s				= raycaster [s]tate struct;
* width_ratio	= convertion ration from px width to abstract interval of 0 to 2;
* px_col_x		= cur px being iterated and calculated;
* s.cam_x			= px_col_x converted to -1 to 1 interval;
* player_x/y.dir= player angle converted to sin and cos coordinates -1 to 1
* s.plane[x/y]	= right and left limit rays of the view;
* player_x/y.tile	= the tile where the player is;
* player_x/y.offset	= offset within the tile where the player is;
* ray_x/y.dir		= direction sin and cos of the ray being calculated
* ray_x/y.delta_dist= distance needed to cross one cell in the ray dir;
* ray_x/y.delta_dist= distance needed to cross one cell in x/y dir;
*/
static void	digital_diff_analys(t_map *map, t_caster *c)
{
	const double	x_delta_dist = c->ray_x.delta_dist;
	const double	y_delta_dist = c->ray_y.delta_dist;
	const int		x_step = c->ray_x.step;
	const int		y_step_row = c->ray_y.step * map->size[y];
	char			*cur_cell;

	cur_cell = &map->grid[c->player_y.tile][c->player_x.tile];
	while (*cur_cell != '1')
	{
		if (c->ray_x.side_dist < c->ray_y.side_dist)
		{
			c->ray_x.side_dist += x_delta_dist;
			cur_cell += x_step;
			c->wall_side = x;
		}
		else
		{
			c->ray_y.side_dist += y_delta_dist;
			cur_cell += y_step_row;
			c->wall_side = y;
		}
	}
}

static void	init_axis(t_axis *axis, double player_offset)
{
	if (axis->dir == 0)
		axis->delta_dist = INT_MAX;
	else
		axis->delta_dist = fabs(1 / axis->dir);
	if (axis->dir < 0)
	{
		axis->step = -1;
		axis->side_dist = player_offset * axis->delta_dist;
	}
	else
	{
		axis->step = 1;
		axis->side_dist = (1.0 - player_offset) * axis->delta_dist;
	}
}

static void	split_player_tile_and_offset(
	t_s_player *player_axis, double map_pos)
{
	player_axis->tile = (int)map_pos;
	player_axis->offset = map_pos - player_axis->tile;
}

void	raycasting(t_game *g)
{
	const double	width_ratio = 2.0 / g->map.size[y];
	t_caster		s;

	s.player_x.dir = cosf(g->player.angle);
	s.player_y.dir = sinf(g->player.angle);
	s.plane[x] = s.player_y.dir * 0.66;
	s.plane[y] = s.player_x.dir * 0.66;
	split_player_tile_and_offset(&s.player_x, g->player.pos[x]);
	split_player_tile_and_offset(&s.player_y, g->player.pos[y]);
	s.px_col_x = 0;
	while (s.px_col_x < g->map.size[y])
	{
		s.cam_x = s.px_col_x * width_ratio - 1;
		s.ray_x.dir = s.player_x.dir + s.plane[x] * s.cam_x;
		s.ray_y.dir = s.player_y.dir + s.plane[y] * s.cam_x;
		init_axis(&s.ray_x, s.player_x.offset);
		init_axis(&s.ray_y, s.player_y.offset);
		digital_diff_analys(&g->map, &s);
		if (s.wall_side == x)
			s.wall_dist = s.ray_x.side_dist - s.ray_x.delta_dist;
		else
			s.wall_dist = s.ray_y.side_dist - s.ray_y.delta_dist;
		// draw_column();
		s.px_col_x++;
	}
}
