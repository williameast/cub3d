/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 17:24:20 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	init_game(t_game *game, char *filename)
{
	int			map_begin_offset;
	t_parse		parse = {0};

	map_begin_offset = parse_config_data(&parse, &game->config, filename);
	if (map_begin_offset == -1)
		return (handle_error("Error: Missing or invalid config data", game));
	parse.raw_map_string = parse.raw_file_string + map_begin_offset;
	if (create_map(&game->map, parse.raw_map_string))
		return (1);
	debug_config(&parse, &game->config, &game->map);
	return (0);
}

int	init_window(t_window *window)
{
	window->width = WIDTH;
	window->height = HEIGHT;
	window->mlx = mlx_init(window->width,
			window->height, WIN_NAME, false);
	if (!window->mlx)
		return (1);
	window->img = mlx_new_image(window->mlx,
								window->width,
								window->height);
	if (!window->img)
	{
		mlx_terminate(window->mlx);
		return (1);
	}
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) < 0)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		return (1);
	}
	return (0);
}

void	cleanup_window(t_window *window)
{
	if (window->img)
		mlx_delete_image(window->mlx, window->img);
	window->img = NULL;
	if (window->mlx)
		mlx_terminate(window->mlx);
	window->mlx = NULL;
}
