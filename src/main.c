/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/10/06 12:51:16 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_window	window;
	t_map		map = {0};

	int	i = 0;
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	if (init_window(&window) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize game\n", 2);
		return (1);
	}
	printf("Opening %s %i\n", argv[1], i);
	read_map_as_string(&map, argv[1]);
	get_map_max_dimensions(&map);
	mlx_key_hook(window.mlx, key_hook, &window);
	mlx_loop(window.mlx);
	cleanup_window(&window);
	cleanup_map(&map);
	return (0);
}
