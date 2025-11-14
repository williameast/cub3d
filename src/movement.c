/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 12:27:52 by weast             #+#    #+#             */
/*   Updated: 2025/11/14 11:33:47 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

static int	validate_move(t_map *map, float new_x, float new_y)
{
	int	x;
	int	y;

	x = (int)new_x;
	y = (int)new_y;
	if (map->grid[y][x] == '1')
		return (0);
	return (1);
}

void	walk(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.pos[x];
	new_y = game->player.pos[y];
	game->player.dir[x] = cosf(game->player.angle);
	game->player.dir[y] = sinf(game->player.angle);
	if (game->render.key_state[KEY_W])
		calculate_walk(game->player.dir, &new_x, &new_y, 1);
	if (game->render.key_state[KEY_S])
		calculate_walk(game->player.dir, &new_x, &new_y, -1);
	if (game->render.key_state[KEY_D])
		calculate_strafe(game->player.dir, &new_x, &new_y, 1);
	if (game->render.key_state[KEY_A])
		calculate_strafe(game->player.dir, &new_x, &new_y, -1);
	if (validate_move(&game->map, new_x, new_y))
	{
		game->player.pos[x] = new_x;
		game->player.pos[y] = new_y;
	}
}

void	see(t_game *game)
{
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
