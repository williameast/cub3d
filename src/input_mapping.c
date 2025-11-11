/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:25:40 by weast             #+#    #+#             */
/*   Updated: 2025/11/11 19:34:30 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>
#include <mlx.h>

int handle_keypress(int keycode, void *param)
{
	t_render *render;

	render = (t_render *)param;

	render->key_state[keycode] = 1;

	// handle hitting X to close.
	if (keycode == XK_Escape)
	{
		mlx_loop_end(render->mlx);
		mlx_destroy_window(render->mlx, render->win);
	}
	return (0);
}

int handle_keyrelease(int keycode, void *param)
{
	t_render *render;

	render = (t_render *)param;
	render->key_state[keycode] = 0;
	return (0);
}
