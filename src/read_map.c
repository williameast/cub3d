/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:28 by weast             #+#    #+#             */
/*   Updated: 2025/10/07 16:14:16 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// INFO: map object is bzeroed in main.
// raw_map_string already points to start of map data
static int	get_map_max_dimensions(t_map *map, char *raw_map_string)
{
	int row_len;
	int i;

	i = 0;
	row_len = 0;
	map->size[y] = 0;
	while (raw_map_string[i])
	{
		if (raw_map_string[i] == '\n')
		{
			if (row_len > 0)
			{
				map->size[y]++;
				if (row_len > map->size[x])
					map->size[x] = row_len;
			}
			row_len = 0;
		}
		else
			row_len++;
		i++;
	}
	return (0);
}

static int validate_map_chars(char *raw_map_string)
{
	int i;
	int spawn;

	i = 0;
	spawn = 0;
	while (raw_map_string[i])
	{
		if (ft_strchr(MAP_VALID_PLAYER_CHARS, raw_map_string[i]))
		{
			if (!spawn)
				spawn = 1;
			else
				return (1);
			i++;
		}
		if (ft_strchr(MAP_VALID_ENV_CHARS, raw_map_string[i]))
			i++;
		else
			return (1);
	}
	if (!spawn)
		return (1);
	else
		return (0);
}

int	create_map(t_map *map, char *raw_map_string)
{
	if (validate_map_chars(raw_map_string))
		return(ft_putstr_fd("Invalid characters in map.", STDERR_FILENO));
	get_map_max_dimensions(map, raw_map_string);
	if (allocate_game_map(map, raw_map_string))
		return(ft_putstr_fd("Could not allocate map grid.\n", STDERR_FILENO));
	return (0);
}
