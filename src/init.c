/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/10/23 17:38:03 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_img(t_img *img, t_render *render, size_t width, size_t height)
{
	img->width = width;
	img->height = height;
	img->img = mlx_new_image(
			render->mlx,
			img->width,
			img->height);
	if (!img->img)
		return (perror("Init_img: "), ERR);
	img->addr = mlx_get_data_addr(
			img->img,
			&img->bits_per_pixel,
			&img->size_line,
			&img->endian);
	return (OK);
}

int	init_sprite(t_img *img, char *path, t_render *render, int size)
{
	img->width = size;
	img->height = size;
	img->img = mlx_xpm_file_to_image(
			render->mlx,
			path,
			&img->width,
			&img->height);
	if (!img->img)
		return (perror("Init_sprite: "), ERR);
	img->addr = mlx_get_data_addr(
			img->img,
			&img->bits_per_pixel,
			&img->size_line,
			&img->endian);
	return (OK);
}

int	transpose_texture(t_img *tmp, t_img *tex)
{
	int	X;
	int	Y;
	int	line_len_in_px;
	int	i_px_color_src;
	int	i_px_dest;

	Y = 0;
	line_len_in_px = (tmp->size_line >> 2);
	while (Y < tmp->height)
	{
		X = 0;
		while (X < tmp->width)
		{
			i_px_color_src = Y * line_len_in_px + X;
			i_px_dest = X * line_len_in_px + Y;
			tex->addr[i_px_dest] = tmp->addr[i_px_color_src];
			X++;
		}
		Y++;
	}
	return (OK);
}

int	load_trans_textures(t_game *g, t_render *r)
{
	t_img	tmp_tex;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (init_img(&g->config.tex[i], r, 128, 128) != OK
			|| init_sprite(&tmp_tex, g->config.tex_path[i], r, 128) != OK
			|| transpose_texture(&tmp_tex, &g->config.tex[i]) != OK)
			return (perror_and_clean("load_trans_textures: ", g));
		mlx_destroy_image(r->mlx, tmp_tex.img);
		i++;
	}
	return (OK);
}

int	init_render(t_game *g, t_render *r)
{
	r->mlx = mlx_init();
	if (!r->mlx)
		return (perror("Init_render: "), ERR);
	if (!mlx_get_screen_size(r->mlx, &r->width, &r->height))
		return (ERR);
	r->win = mlx_new_window(r->mlx, r->width, r->height, WIN_NAME);
	if (!r->win)
		return (perror("Init_render: "), cleanup_all(g, r), ERR);
	if (init_img(&r->front, r, r->width, r->height) != OK
		|| init_img(&r->back, r, r->width, r->height) != OK
		|| init_img(&r->minimap, r, r->width, r->height) != OK
		|| load_trans_textures(g, r) != OK)
		return (cleanup_all(g, r), ERR);
	return (OK);
}
