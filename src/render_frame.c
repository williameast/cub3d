/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:25:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/11 18:53:55 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "raycaster.h"


int	render_frame(void *game)
{
	t_game		*g;
	t_render	*r;
	t_img		*b;

	g = game;
	r = &g->render;
	b = g->render.back;
	move(g);
	raycasting(g);
	draw_minimap(g);
	draw_minimap(g);
	mlx_put_image_to_window(r->mlx, r->win, b->img, 0, 0);
	r->back = r->front;
	r->front = b;
	return (OK);
}
