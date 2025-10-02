/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:28 by weast             #+#    #+#             */
/*   Updated: 2025/10/02 13:32:28 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"
#include <stdio.h>

int	get_map_max_dimensions(t_map *map)
{
	int row_len;
	int i;

	i = 0;
	while (map->raw_map_string[i])
	{
		row_len++;
		if (map->raw_map_string[i] == '\n')
		{
			map->dimension.y++;
			if (row_len > map->dimension.x)
				map->dimension.x = row_len;
			row_len = 0;
		}
		i++;
	}
	puts("Map dimensions:");
	debug_crd(map->dimension);
	return (0);
}
