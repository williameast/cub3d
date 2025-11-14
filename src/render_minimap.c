/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:45:40 by weast             #+#    #+#             */
/*   Updated: 2025/11/14 12:33:12 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_tiles(t_game *game)
{
	int	scale;
	int	offset[2];
	int	map_pos[2];
	int	point[2];

	scale = 5;
	offset[x] = 5;
	offset[y] = 5;
	map_pos[y] = 0;
	while (map_pos[y] < game->map.size[y])
	{
		map_pos[x] = 0;
		while (map_pos[x] < game->map.size[x])
		{
			if (game->map.grid[map_pos[y]][map_pos[x]] == '1')
			{
				point[x] = offset[x] + map_pos[x] * scale;
				point[y] = offset[y] + map_pos[y] * scale;
				put_square(game->render.back, point, scale, 0xFFFFFF);
			}
			map_pos[x]++;
		}
		map_pos[y]++;
	}
}

static void	draw_player(t_game *game)
{
	int	scale;
	int	offset[2];
	int	point[2];

	scale = 5;
	offset[x] = 5;
	offset[y] = 5;
	point[x] = offset[x] + (int)(game->player.pos[x] * scale) - 2;
	point[y] = offset[y] + (int)(game->player.pos[y] * scale) - 2;
	put_square(game->render.back, point, 4, 0xFF0000);
}

void	draw_minimap(t_game *game)
{
	draw_map_tiles(game);
	draw_player(game);
}
