/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:19:33 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 13:35:34 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	debug_map(t_map *map)
{
	int i;
	int j;

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
	printf("	North: %s\n", config->tex_no);
	printf("	South: %s\n", config->tex_so);
	printf("	East : %s\n", config->tex_ea);
	printf("	West : %s\n", config->tex_we);
	printf("\n  COLOURS\n\n");
	printf("	Floor: %i\n", config->col_floor);
	printf("	Ceil : %i\n", config->col_ceiling);

	printf(" LAYOUT\n\n");
	debug_map(map);
}
