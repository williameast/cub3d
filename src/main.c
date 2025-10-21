/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/10/21 21:50:02 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	init_engine(t_game *game)
{
	mlx_key_hook(game->win.win, key_hook, &game->win);
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
		&& init_window(&game.win) == OK
		&& init_engine(&game) == OK)
		mlx_loop(game.win.mlx);
	cleanup_all(&game);
	return (game.exit_code);
}
