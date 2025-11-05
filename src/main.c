/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/11/05 13:42:22 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/X.h>

int handle_keypress(int keycode, void *param);
int handle_keyrelease(int keycode, void *param);

int	init_engine(t_game *game)
{
	/* mlx_key_hook(game->render.win, key_hook, &game->render.win); */
	mlx_loop_hook(game->render.mlx, render_frame, game);
	mlx_hook(game->render.win, KeyPress, KeyPressMask, &handle_keypress, &game->render);
	mlx_hook(game->render.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &game->render);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;

	ft_bzero(&game, sizeof(game));
	if (argc != 2)
		return (handle_error("Usage: ./cub3d <map.cub>\n", &game, INVALID));
	if (parse_map(&game, argv[1]) == OK
		&& map_is_closed(&game.map, game.player.pos, &game) == OK
		&& init_window(&game, &game.render) == OK
		&& init_engine(&game) == OK)
		mlx_loop(game.render.mlx);
	cleanup_all(&game, &game.render);
	return (game.exit_code);
}
