/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/10/07 10:39:51 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_window	window;
	t_map		map = {0};
	t_config	config = {0};
	int			offset;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	offset = parse_config_data(&config, argv[1]);
	if (offset == -1)
	{
		cleanup_config(&config);
		ft_putstr_fd("Error: Missing or invalid config data\n", 2);
		return (1);
	}
	map.y_offset = offset;
	map.raw_map_string = config.raw_file_string + map.y_offset;
	if (create_map(&map))
	{
		cleanup_config(&config);
		return (1);
	}
	if (init_window(&window) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize game\n", 2);
		return (1);
	}
	debug_config(&config, &map);
	mlx_key_hook(window.mlx, key_hook, &window);
	mlx_loop(window.mlx);
	cleanup_window(&window);
	cleanup_map(&map);
	cleanup_config(&config);
	return (0);
}
