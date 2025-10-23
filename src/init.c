/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/10/23 12:04:25 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_img(t_img *img, t_render *render, size_t width, size_t hight)
{
	img->width = width;
	img->hight = hight;
	img->img = mlx_new_image(
			render->mlx,
			img->width,
			img->hight);
	if (!img->img)
		return (perror("Init_img: "), ERR);
	img->data = mlx_get_data_addr(
			img->img,
			&img->bits_per_pixel,
			&img->size_line,
			&img->endian);
	return (OK);
}

int	init_render(t_game *g, t_render *r)
{
	int	i;

	r->mlx = mlx_init();
	if (!r->mlx)
		return (perror("Init_render: "), ERR);
	if (!mlx_get_screen_size(r->mlx, r->width, r->hight))
		return (ERR);
	r->win = mlx_new_window(r->mlx, r->width, r->hight, WIN_NAME);
	if (!r->win)
		return (perror("Init_render: "), cleanup_all(g, r), ERR);
	if (init_img(r->front, r, r->width, r->hight) != OK
		|| init_img(r->back, r, r->width, r->hight) != OK
		|| init_img(r->minimap, r, r->width, r->hight) != OK)
		return (cleanup_all(g, r), ERR);
	i = 0;
	while (i < 4)
		if (init_img(&g->config.tex[i], r, 128, 128) != OK)
			return (perror("Init_render: "), cleanup_all(g, r), ERR);
	return (OK);
}
