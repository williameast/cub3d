/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:28:45 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/12 11:54:03 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include <math.h>

/*
* s					= raycaster [s]tate struct;
* width_ratio		= ration from px width to abstract interval of 0 to 2;
* px_col_x			= cur px being iterated and calculated;
* s.cam_x			= px_col_x converted to -1 to 1 interval;
* x.player/y.dir	= player angle converted to sin and cos coordinates -1 to 1
* s.plane[x/y]		= right and left limit rays of the view;
* x.player/y.tile	= the tile where the player is;
* x.player/y.offset	= offset within the tile where the player is;
* ray_x/y.dir		= direction sin and cos of the ray being calculated
* ray_x/y.delta_dist= distance needed to cross one cell in the ray dir;
* ray_x/y.delta_dist= distance needed to cross one cell in x/y dir;
*/
static void	digital_diff_analys(t_map *map, t_caster *s)
{
	const double	x_delta_dist = s->x.delta_dist;
	const double	y_delta_dist = s->y.delta_dist;
	const int		x_step = s->x.step;
	const int		y_step_row = s->y.step * map->size[x];
	char			*cur_cell;

	cur_cell = &map->grid[s->y.player_tile][s->x.player_tile];
	while (*cur_cell != '1')
	{
		if (s->x.side_dist < s->y.side_dist)
		{
			s->x.side_dist += x_delta_dist;
			cur_cell += x_step;
			s->wall_side = x;
		}
		else
		{
			s->y.side_dist += y_delta_dist;
			cur_cell += y_step_row;
			s->wall_side = y;
		}
	}
}

static void	init_player_axis(t_axis *axis, double player_dir, double map_pos)
{
	axis->plane = player_dir * 0.66;
	axis->player_tile = (int)map_pos;
	axis->player_offset = map_pos - axis->player_tile;
}

static void	init_axis(t_axis *axis, double player_offset, double cam_x)
{
	axis->ray_dir = axis->player_dir + axis->plane * cam_x;
	if (axis->ray_dir == 0)
		axis->delta_dist = INT_MAX;
	else
		axis->delta_dist = fabs(1 / axis->ray_dir);
	if (axis->ray_dir < 0)
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

void	raycasting(t_game *g)
{
	const double	width_ratio = 2.0 / g->render.width;
	t_caster		s;

	s.x.player_dir = cosf(g->player.angle);
	s.y.player_dir = sinf(g->player.angle);
	init_player_axis(&s.x, s.y.player_dir, g->player.pos[x]);
	init_player_axis(&s.y, -s.x.player_dir, g->player.pos[y]);
	s.px_col_x = 0;
	while (s.px_col_x < g->render.width)
	{
		s.cam_x = s.px_col_x * width_ratio - 1;
		init_axis(&s.x, s.x.player_offset, s.cam_x);
		init_axis(&s.y, s.y.player_offset, s.cam_x);
		digital_diff_analys(&g->map, &s);
		if (s.wall_side == x)
			s.wall_dist = s.x.side_dist - s.x.delta_dist;
		else
			s.wall_dist = s.y.side_dist - s.y.delta_dist;
		draw_column(g, &s, g->render.back);
		s.px_col_x++;
	}
}
