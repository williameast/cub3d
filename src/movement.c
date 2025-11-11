/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:27:52 by weast             #+#    #+#             */
/*   Updated: 2025/11/11 19:36:39 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <math.h>


#define VELOCITY 0.01


int validate_move(t_map *map, float new_x, float new_y)
{
	int X;
	int Y;

	X = (int) new_x;
	Y = (int) new_y;

	/* printf("x: %f, y: %f\n", new_x, new_y); */
	/* printf("map: %i, %i\n", map->size[0], map->size[1]); */
	/* if (X < 0 || Y < 0 || */
	/* 	Y >= map->size[0] || X >= map->size[1]) */
	/* { */
	/* 	return (0); */
	/* } */

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

	if (game->render.key_state[XK_w])
	{
		new_x += game->player.dir[x] * VELOCITY;
		new_y += game->player.dir[y] * VELOCITY;
	}
	if (game->render.key_state[XK_s])
	{
		new_x -= game->player.dir[x] * VELOCITY;
		new_y -= game->player.dir[y] * VELOCITY;
	}
	if (game->render.key_state[XK_d])
	{
		new_x += game->player.dir[y] * VELOCITY;
		new_y -= game->player.dir[x] * VELOCITY;
	}
	if (game->render.key_state[XK_a])
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
	if (game->render.key_state[XK_Left])
		game->player.angle += VELOCITY;
	if (game->render.key_state[XK_Right])
		game->player.angle -= VELOCITY;
}

void	move(t_game *game)
{
	walk(game);
	see(game);
}
