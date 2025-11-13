/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:28:45 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/13 22:41:59 by dimachad         ###   ########.fr       */
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

enum e_perpendicular
{
	POS,
	RAY,
};

static int	is_door_blocking(int x_y, char *cur_cell,
						t_axis **axis, t_caster *s)
{
	s->wall_dist = axis[x_y]->side_dist - axis[x_y]->delta_dist;
	s->draw.wall_x_ratio = axis[!x_y]->player_pos
		+ s->wall_dist * axis[!x_y]->ray_dir;
	s->draw.wall_x_ratio -= floor(s->draw.wall_x_ratio);
	if (cur_cell != s->last_door_cell)
	{
		s->last_door_cell = cur_cell;
		s->door_open_ratio = 0.0;
		if (s->wall_dist < 2.0)
			s->door_open_ratio = 1.0 - s->wall_dist / 2.0;
	}
	if (s->draw.wall_x_ratio < s->door_open_ratio)
		return (0);
	return (1);
}

static void	digital_diff_analys(t_map *map, t_caster *s)
{
	const int	step_y_row = s->y.step * map->size[x];
	const int	step[2] = {s->x.step, step_y_row};
	t_axis		*axis[2];
	char		*cur_cell;
	int			x_y;

	cur_cell = &map->grid[s->y.player_tile][s->x.player_tile];
	axis[x] = &s->x;
	axis[y] = &s->y;
	while (*cur_cell != '1')
	{
		x_y = s->x.side_dist >= s->y.side_dist;
		s->wall_side = x_y;
		axis[x_y]->side_dist += axis[x_y]->delta_dist;
		cur_cell += step[x_y];
		if (*cur_cell == 'D'
			&& is_door_blocking(x_y, cur_cell, axis, s))
			return ;
	}
	s->last_door_cell = NULL;
	s->wall_dist = axis[x_y]->side_dist - axis[x_y]->delta_dist;
	s->draw.wall_x_ratio = axis[!x_y]->player_pos
		+ s->wall_dist * axis[!x_y]->ray_dir;
	s->draw.wall_x_ratio -= floor(s->draw.wall_x_ratio);
}

static void	init_player_axis(t_axis *axis, double player_dir, double map_pos)
{
	axis->player_pos = map_pos;
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

	s.last_door_cell = NULL;
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
		draw_column(g, &s, g->render.back);
		s.px_col_x++;
	}
}
