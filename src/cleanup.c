/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:50:16 by weast             #+#    #+#             */
/*   Updated: 2025/10/23 11:50:22 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	*free_and_null_img(void *img, t_render *render)
{
	if (img)
		mlx_destroy_image(render->mlx, img);
	return (NULL);
}

void	cleanup_all(t_game *g, t_render *r)
{
	int	i;

	i = 0;
	while (i < 4)
		g->config.tex[i] = free_and_null_img(&g->config.tex[i], r);
	r->back = free_and_null_img(r->back, r);
	r->front = free_and_null_img(r->front, r);
	r->minimap = free_and_null_img(r->minimap, r);
	if (r->win)
		mlx_destroy_window(r->mlx, r->win);
	r->win = NULL;
	if (r->mlx)
		mlx_destroy_display(r->mlx);
	r->mlx = NULL;
	if (g->map.grid)
		free(g->map.grid);
	g->map.grid = NULL;
}
