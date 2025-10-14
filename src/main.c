/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 14:58:43 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d.h"
#include <unistd.h>

int	init_game(t_game *game, t_parse *parse, char *filename)
{
	int	offset;

	offset = parse_config_data(parse, &game->config, filename);
	if (offset == -1)
	{
		cleanup_parse(parse);
		cleanup_config(&game->config);
		ft_putstr_fd("Error: Missing or invalid config data\n", STDERR_FILENO);
		return (1);
	}
	parse->raw_map_string = parse->raw_file_string + offset;
	if (create_map(&game->map, parse->raw_map_string))
	{
		cleanup_parse(parse);
		cleanup_config(&game->config);
		ft_putstr_fd("Error: failed to create map\n", STDERR_FILENO);
		return (1);
	}
	debug_config(parse, &game->config, &game->map);
	cleanup_parse(parse);
	return (0);
}

int	init_engine(t_game *game)
{
	mlx_key_hook(game->win.mlx, key_hook, &game->win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_parse		parse;

	if (argc != 2)
		return (perror("Usage: ./cub3d <map.cub>\n"), ERR);
	if (init_game(&game, &parse, argv[1]) == OK
		&& map_is_closed(&game.map, game.player.pos) == OK
		&& init_window(&game.win) == OK
		&& init_engine(&game) == OK)
		mlx_loop(game.win.mlx);
	cleanup_all(&game);
	return (game.exit_code);
}
