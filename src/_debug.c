/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:19:33 by weast             #+#    #+#             */
/*   Updated: 2025/10/07 10:45:26 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	debug_2D(t_2D point)
{
	printf("(%d, %d)\n", point.x, point.y);
}

void	debug_map(t_map *map)
{
	int x;
	int y;

	x = 0;
	y = 0;

	while (y < map->dimension.y)
	{
		while (x < map->dimension.x)
		{
			printf("%c", GRID(x, y));
			x++;
		}
		x = 0;
		printf("\n");
		y++;
	}
}

void	debug_config(t_config *config, t_map *map)
{
	printf("PREAMBLE\n\n");
	printf("  TEXTURES\n\n");
	printf("	North: %s\n", config->tex_no);
	printf("	South: %s\n", config->tex_so);
	printf("	East : %s\n", config->tex_ea);
	printf("	West : %s\n", config->tex_we);
	printf("\n  COLOURS\n\n");
	printf("	Floor: %s\n", config->col_floor_raw);
	printf("	Ceil : %s\n", config->col_ceiling_raw);

	printf("\nMAP DIMENSION: ");
	debug_2D(map->dimension);
	printf(" LAYOUT\n\n");
	debug_map(map);
}
