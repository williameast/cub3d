/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:28 by weast             #+#    #+#             */
/*   Updated: 2025/10/06 12:51:17 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

static int	check_extension(char *filename)
{
	int	ext_len;
	int	name_len;

	ext_len = ft_strlen(FILE_EXT);
	name_len = ft_strlen(filename);
	if (ext_len >= name_len)
		return (0);
	return (!ft_strncmp(FILE_EXT, &filename[name_len - ext_len], 5));
}

int	read_map_as_string(t_map *map, char *filename)
{
	int	fd;
	char *line;
	char *temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || !check_extension(filename))
		return (1);
	map->raw_map_string = ft_strdup("");
	if (!map->raw_map_string)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = ft_strjoin(map->raw_map_string, line);
		free(map->raw_map_string);
		if (!temp)
		{
			free(line);
			return (1);
		}
		map->raw_map_string = temp;
		free(line);
	}
	close(fd);
	return (0);
}

int	get_map_max_dimensions(t_map *map)
{
	int row_len;
	int i;

	i = 0;
	row_len = 0;
	while (map->raw_map_string[i])
	{
		if (map->raw_map_string[i] == '\n')
		{
			if (row_len > 0)
			{
				map->dimension.y++;
				if (row_len > map->dimension.x)
					map->dimension.x = row_len;
			}
			row_len = 0;
		}
		else
			row_len++;
		i++;
	}
	puts("Map dimensions:");
	debug_2D(map->dimension);
	return (0);
}


