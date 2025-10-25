/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:50:16 by weast             #+#    #+#             */
/*   Updated: 2025/10/25 02:28:02 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	*free_and_null_img(t_img *img, t_render *render)
{
	if (img->img)
		mlx_destroy_image(render->mlx, img->img);
	return (NULL);
}

void	cleanup_all(t_game *g, t_render *r)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g->config.tex[i].img = free_and_null_img(&g->config.tex[i], r);
		i++;
	}
	r->back->img = free_and_null_img(r->back, r);
	r->front->img = free_and_null_img(r->front, r);
	r->minimap.img = free_and_null_img(&r->minimap, r);
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

int	perror_and_clean(char *err_str, t_game *g)
{
	return (
		perror(err_str),
		cleanup_all(g, &g->render),
		ERR);
}
