/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/10/07 16:28:38 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	init_engine(t_game *game);


int	main(int argc, char **argv)
{
	t_window	window;
	t_game		game;
	t_parse		parse;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", STDERR_FILENO);
		return (1);
	}
	if (init_game(&game, &parse, argv[1]))
		return (1);
	if (init_window(&window) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize game\n", STDERR_FILENO);
		cleanup_map(&game.map);
		cleanup_config(&game.config);
		return (1);
	}
	mlx_key_hook(window.mlx, key_hook, &window);
	mlx_loop(window.mlx);
	cleanup_window(&window);
	cleanup_map(&game.map);
	cleanup_config(&game.config);
	return (0);
}
