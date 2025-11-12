/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:27:52 by weast             #+#    #+#             */
/*   Updated: 2025/11/12 19:00:34 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <math.h>


#define VELOCITY 0.04


int validate_move(t_map *map, float new_x, float new_y)
{
	int X;
	int Y;

	X = (int) new_x;
	Y = (int) new_y;

	if (map->grid[Y][X] == '1')
		return (0);
	return (1);
}

void	walk(t_game *game)
{
	float new_x = game->player.pos[x];
	float new_y = game->player.pos[y];
	game->player.dir[x] = cosf(game->player.angle);
	game->player.dir[y] = sinf(game->player.angle);

	if (game->render.key_state[KEY_W])
	{
		new_x += game->player.dir[x] * VELOCITY;
		new_y += game->player.dir[y] * VELOCITY;
	}
	if (game->render.key_state[KEY_S])
	{
		new_x -= game->player.dir[x] * VELOCITY;
		new_y -= game->player.dir[y] * VELOCITY;
	}
	if (game->render.key_state[KEY_D])
	{
		new_x += game->player.dir[y] * VELOCITY;
		new_y -= game->player.dir[x] * VELOCITY;
	}
	if (game->render.key_state[KEY_A])
	{
		new_x -= game->player.dir[y] * VELOCITY;
		new_y += game->player.dir[x] * VELOCITY;
	}
	if (validate_move(&game->map, new_x, new_y))
	{
		game->player.pos[x] = new_x;
		game->player.pos[y] = new_y;
	}
}

void	see(t_game *game)
{
	// SET orientation depending on NESW!
	if (game->render.key_state[KEY_LEFT])
		game->player.angle += VELOCITY;
	if (game->render.key_state[KEY_RIGHT])
		game->player.angle -= VELOCITY;
}

void	move(t_game *game)
{
	walk(game);
	see(game);
}
