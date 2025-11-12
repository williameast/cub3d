/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:25:40 by weast             #+#    #+#             */
/*   Updated: 2025/11/12 20:09:59 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>
#include <mlx.h>

t_key	keycode_to_key(int keycode)
{
	if (keycode == XK_w)
		return (KEY_W);
	if (keycode == XK_a)
		return (KEY_A);
	if (keycode == XK_s)
		return (KEY_S);
	if (keycode == XK_d)
		return (KEY_D);
	if (keycode == XK_Left)
		return (KEY_LEFT);
	if (keycode == XK_Right)
		return (KEY_RIGHT);
	if (keycode == XK_x)
		return (KEY_X);
	if (keycode == XK_Escape)
		return (KEY_ESCAPE);
	return (KEY_INVALID);
}

int handle_keypress(int keycode, void *param)
{
	t_game	*game;
	t_key		key;

	game = (t_game *)param;
	key = keycode_to_key(keycode);
	game->render.key_state[key] = 1;
	if (key == KEY_ESCAPE)
		clean_exit(game);
	return (0);
}

int handle_keyrelease(int keycode, void *param)
{
	t_game	*game;
	t_key		key;

	game = (t_game *)param;
	key = keycode_to_key(keycode);
	game->render.key_state[key] = 0;
	return (0);
}
