/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:19:33 by weast             #+#    #+#             */
/*   Updated: 2025/10/23 22:06:34 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	debug_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->size[y])
	{
		while (j < map->size[x])
		{
			printf("%c", map->grid[i][j]);
			j++;
		}
		j = 0;
		printf("\n");
		i++;
	}
}

void	debug_config(t_config *config, t_map *map)
{
	printf("PREAMBLE\n\n");
	printf("  TEXTURES\n\n");
	printf("	North: %s\n", config->tex_path[0]);
	printf("	South: %s\n", config->tex_path[1]);
	printf("	East : %s\n", config->tex_path[2]);
	printf("	West : %s\n", config->tex_path[3]);
	printf("\n  COLOURS\n\n");
	printf("	Floor: %i\n", config->col_floor);
	printf("	Ceil : %i\n", config->col_ceiling);
	printf(" LAYOUT\n\n");
	debug_map(map);
}

void	debug_game(t_game *game)
{
	debug_config(&game->config, &game->map);
}
