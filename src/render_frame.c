/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:25:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/11 18:35:06 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "raycaster.h"

int	render_frame(void *game)
{
	t_game		*g;
	t_render	*r;
	t_img		*back;

	g = game;
	r = &g->render;
	back = g->render.back;
	move(g);
	raycasting(g);
	mlx_put_image_to_window(r->mlx, r->win, back->img, 0, 0);
	r->back = r->front;
	r->front = back;
	return (OK);
}
