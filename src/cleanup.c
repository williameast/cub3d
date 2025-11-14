/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:50:16 by weast             #+#    #+#             */
/*   Updated: 2025/11/14 13:42:41 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	*free_and_null_img(t_img *img, t_render *render)
{
	if (img->img)
		mlx_destroy_image(render->mlx, img->img);
	return (NULL);
}

void	*free_and_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	cleanup_all(t_game *g, t_render *r)
{
	t_config	*c;
	int			i;

	c = &g->config;
	i = 0;
	while (i < 4)
	{
		c->tex[i].img = free_and_null_img(&c->tex[i], r);
		c->tex_path[i] = free_and_null(c->tex_path[i]);
		i++;
	}
	if (r->back)
		r->back->img = free_and_null_img(r->back, r);
	if (r->front)
		r->front->img = free_and_null_img(r->front, r);
	if (r->win)
		mlx_destroy_window(r->mlx, r->win);
	r->win = NULL;
	if (r->mlx)
		mlx_destroy_display(r->mlx);
	if (r->mlx)
		free_and_null(r->mlx);
	if (g->map.grid)
		free(g->map.grid);
	g->map.grid = NULL;
}
