/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:23:12 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/25 02:59:16 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

static t_img	*get_texture(t_caster *s, t_config *config)
{
	if (s->wall_side == y)
	{
		if (s->y.ray_dir < 0)
			return (&config->tex[SOUTH]);
		return (&config->tex[NORTH]);
	}
	else
	{
		if (s->x.ray_dir < 0)
			return (&config->tex[WEST]);
		return (&config->tex[EAST]);
	}
}

static int	get_tex_color_trans(const t_img *tex, int tex_x, int tex_y)
{
	int	*pixels;
	int	line_len_in_px;

	if (!tex || !tex->addr || tex_x < 0 || tex_x >= tex->width)
		return (0xFF00FF);
	if (tex_y < 0 || tex_y >= tex->height)
		return (0xFF00FF);
	pixels = (int *)tex->addr;
	line_len_in_px = tex->size_line >> 2;
	return (pixels[tex_x * line_len_in_px + tex_y]);
}

static void	calc_tex_params(t_game *g, t_caster *s, t_draw *d)
{
	if (s->wall_side == x)
		d->wall_x_ratio = g->player.pos[y] + s->wall_dist * s->y.ray_dir;
	else
		d->wall_x_ratio = g->player.pos[x] + s->wall_dist * s->x.ray_dir;
	d->wall_x_ratio -= floor(d->wall_x_ratio);
	d->tex_x = d->wall_x_ratio * TEX_SIZE;
	if ((s->wall_side == x && s->x.ray_dir > 0)
		|| (s->wall_side == y && s->y.ray_dir < 0))
		d->tex_x = TEX_SIZE - d->tex_x - 1;
	d->tex_step = (double)TEX_SIZE / (double)d->wall_hight;
}

static void	init_draw_params(t_game *g, t_caster *s, t_draw *d, int img_hight)
{
	const int	screen_center = img_hight >> 1;
	int			half_wall;

	d->wall_hight = img_hight / s->wall_dist;
	half_wall = d->wall_hight >> 1;
	d->px_wall_start = -half_wall + screen_center;
	if (d->px_wall_start < 0)
		d->px_wall_start = 0;
	d->px_wall_end = half_wall + screen_center;
	if (d->px_wall_end >= img_hight)
		d->px_wall_end = img_hight - 1;
	calc_tex_params(g, s, d);
	d->tex_pos = (d->px_wall_start - screen_center + half_wall) * d->tex_step;
}

void	draw_column(t_game *g, t_caster *s, t_img *back)
{
	const t_img	*texture = get_texture(s, &g->config);
	t_draw		d;
	int			color;
	char		*pixel;
	int			py;

	init_draw_params(g, s, &d, g->render.height);
	py = 0;
	while (py < g->render.height)
	{
		pixel = back->addr + py * back->size_line
			+ s->px_col_x * back->bytespp;
		if (py < d.px_wall_start)
			*(int *)pixel = g->config.col_ceiling;
		else if (py <= d.px_wall_end)
		{
			d.tex_y = (int)d.tex_pos & (TEX_SIZE - 1);
			d.tex_pos += d.tex_step;
			color = get_tex_color_trans(texture, d.tex_x, d.tex_y);
			*(int *)pixel = color;
		}
		else
			*(int *)pixel = g->config.col_floor;
		py++;
	}
}
