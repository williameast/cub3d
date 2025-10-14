/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 17:16:14 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_engine(t_game *game)
{
	mlx_key_hook(game->win.mlx, key_hook, &game->win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game = {0};

	if (argc != 2)
		return (perror("Usage: ./cub3d <map.cub>\n"), ERR);
	if (parse_map(&game, argv[1]) == OK
		&& map_is_closed(&game.map, game.player.pos, &game) == OK
		&& init_window(&game.win) == OK
		&& init_engine(&game) == OK)
		mlx_loop(game.win.mlx);
	cleanup_all(&game);
	printf("exit code: %i", game.exit_code);
	return (game.exit_code);
}
