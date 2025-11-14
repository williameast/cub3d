/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/11/14 12:07:56 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "init.h"

int	init_img(t_img *img, t_render *render, size_t width, size_t height)
{
	img->width = width;
	img->height = height;
	img->img = mlx_new_image(render->mlx, img->width, img->height);
	if (!img->img)
		return (perror("Init_img: "), ERR);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	img->bytespp = img->bits_per_pixel >> 3;
	mlx_put_image_to_window(render->mlx, render->win, img->img, 0, 0);
	return (OK);
}

int	init_sprite(t_img *img, char *path, t_render *render)
{
	img->img = mlx_xpm_file_to_image(render->mlx, path, &img->width,
			&img->height);
	if (!img->img)
		return (ft_putstr_fd("Error: sprite not found: ", 2), ft_putstr_fd(path,
				2), ERR);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	img->bytespp = img->bits_per_pixel >> 3;
	return (OK);
}

int	transpose_texture(t_img *tmp, t_img *tex)
{
	int		X;
	int		Y;
	t_trans	t;

	t.line_len_in_px_src = (tmp->size_line >> 2);
	t.line_len_in_px_dst = (tex->size_line >> 2);
	t.src_addr = (int *)tmp->addr;
	t.dst_addr = (int *)tex->addr;
	Y = 0;
	while (Y < tmp->height)
	{
		X = 0;
		while (X < tmp->width)
		{
			t.i_px_color_src = Y * t.line_len_in_px_src + X;
			t.i_px_dest = X * t.line_len_in_px_dst + Y;
			t.dst_addr[t.i_px_dest] = t.src_addr[t.i_px_color_src];
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
		if (init_sprite(&tmp_tex, g->config.tex_path[i], r) != OK
			|| init_img(&g->config.tex[i], r, tmp_tex.height,
				tmp_tex.width) != OK
			|| transpose_texture(&tmp_tex, &g->config.tex[i]) != OK)
			return (perror_and_clean("load_trans_textures: ", g));
		mlx_destroy_image(r->mlx, tmp_tex.img);
		mlx_put_image_to_window(g->render.mlx, g->render.win,
			g->config.tex[i].img, 0, 0);
		i++;
	}
	return (OK);
}

int	init_window(t_game *g, t_render *r)
{
	r->back = &r->frames[0];
	r->front = &r->frames[1];
	r->mlx = mlx_init();
	if (!r->mlx)
		return (perror("Init_render: "), ERR);
	if (!mlx_get_screen_size(r->mlx, &r->width, &r->height))
	{
		r->width = 1280;
		r->height = 720;
	}
	r->win = mlx_new_window(r->mlx, r->width, r->height, WIN_NAME);
	if (!r->win)
		return (perror("Init_render: "), cleanup_all(g, r), ERR);
	if (init_img(r->front, r, r->width, r->height) != OK
		|| init_img(r->back, r, r->width, r->height) != OK
		|| load_trans_textures(g, r) != OK)
		return (cleanup_all(g, r), ERR);
	return (OK);
}
