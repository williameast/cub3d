/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:19:33 by weast             #+#    #+#             */
/*   Updated: 2025/10/06 14:19:50 by weast            ###   ########.fr       */
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
