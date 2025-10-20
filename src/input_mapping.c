/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:25:40 by weast             #+#    #+#             */
/*   Updated: 2025/10/20 14:39:35 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d.h"

static void	calculate_new_position(int dir, double *new_x, double *new_y)
{
	if (dir == NORTH)
	{
		*new_x += MOVEMENT_VELOCITY;
	}
	else if (dir == SOUTH)
	{
		*new_x -= MOVEMENT_VELOCITY;
	}
	else if (dir == EAST)
	{
		*new_y += MOVEMENT_VELOCITY;
	}
	else if (dir == WEST)
	{
		*new_y -= MOVEMENT_VELOCITY;
	}
}

void	handle_movement(int dir, t_game *game)
{
	double	new_x;
	double	new_y;
	double	temp[2];

	new_x = game->player.pos[x];
	new_y = game->player.pos[y];
	calculate_new_position(dir, &new_x, &new_y);
	if ((int)new_x != (int)game->player.pos[x]
		|| (int)new_y != (int)game->player.pos[y])
	{
		temp[x] = new_x;
		temp[y] = new_y;
		if (validate_player_move(&game->map, temp) != OK)
			return ;
	}
	game->player.pos[x] = new_x;
	game->player.pos[y] = new_y;
	printf("Player pos: (%.2f, %.2f)\n", new_x, new_y);
}

// this we use to handle key presses.
void	key_hook(mlx_key_data_t key_press, void *param)
{
	t_game *game = (t_game *)param;
	if (key_press.key == MLX_KEY_ESCAPE && key_press.action == MLX_PRESS)
		mlx_close_window(game->win.mlx);
}
