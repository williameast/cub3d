/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:55:59 by weast             #+#    #+#             */
/*   Updated: 2025/09/09 16:27:44 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "cub3d.h"


int	main(int argc, char **argv)
{
	t_window	window;
	int	i = 0;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./game <map.cub>\n", 2);
		return (1);
	}
	if (init_window(&window) != 0)
	{
		ft_putstr_fd("Error: Failed to initialize game\n", 2);
		return (1);
	}
	printf("Opening %s %i", argv[1], i);

	mlx_key_hook(window.mlx, key_hook, &window);
	mlx_loop(window.mlx);
	cleanup_window(&window);
	return (0);
}
