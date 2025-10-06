/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:30:28 by weast             #+#    #+#             */
/*   Updated: 2025/10/06 14:41:41 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

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

static int	read_map_as_string(t_map *map, char *filename)
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

static int	get_map_max_dimensions(t_map *map)
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
	return (0);
}


int validate_map_chars(t_map *map)
{
	int i;
	int spawn;

	i = 0;
	spawn = 0;
	while (map->raw_map_string[i])
	{
		if (ft_strchr("NESW", map->raw_map_string[i]))
		{
			if (!spawn)
				spawn = 1;
			else
				return (1);
			i++;
		}
		if (ft_strchr(" \n01", map->raw_map_string[i]))
			i++;
		else
			return (1);
	}
	if (!spawn)
		return (1);
	else
		return (0);
}

int	create_map(t_map *map, char *filename)
{
	ft_printf("Opening %s...\n", filename);
	if (read_map_as_string(map, filename))
		return(ft_putstr_fd("Invalid input file.\n", STDERR_FILENO));
	if (validate_map_chars(map))
		return(ft_putstr_fd("Invalid characters in map.", STDERR_FILENO));
	get_map_max_dimensions(map);
	ft_printf("Allocating %s...\n", filename);
	if (allocate_flat_map(map))
		return(ft_putstr_fd("Could not allocate map grid.\n", STDERR_FILENO));

	ft_printf("%s loaded successfully.\n", filename);
	debug_map(map);
	return (0);
}

