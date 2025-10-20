/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:45:00 by weast             #+#    #+#             */
/*   Updated: 2025/10/20 14:45:00 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_input(t_game *game)
{
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->win.mlx);
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_UP))
		handle_movement(NORTH, game);
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_DOWN))
		handle_movement(SOUTH, game);
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_LEFT))
		handle_movement(EAST, game);
	if (mlx_is_key_down(game->win.mlx, MLX_KEY_RIGHT))
		handle_movement(WEST, game);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_input(game);
}
