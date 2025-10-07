/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_contiguous_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: size<sizestudent.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:41:27 by size         #+#    #+#             */
/*   Updated: 2025/10/07 20:05:40 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

// Copies mapstring data into grid system
static void	fill_grid_from_map_string(t_map *map, char *raw_map_string)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (raw_map_string[i])
	{
		if (raw_map_string[i] == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			map->grid[y][x] = raw_map_string[i];
			x++;
		}
		i++;
	}
}

/* Allocates a 2D char array (rows x cols)
 * with a single malloc in contiguous memory
 * for optimize calculation in graphical tight loops:
 *   - First part of the block stores the row pointers (one char* for each row).
 *   - Second part of the block stores all the characters for all rows.
 *   - Each row pointer is then set to the correct offset inside the data block.
 *   NOTE: the whole block must be freed with a single free;
*/
int	allocate_contiguous_map(char ***map, size_t cols, size_t rows)
{
	size_t	pointers_size;
	size_t	row_size;
	char	*cur_row;
	size_t	i;

	pointers_size = rows * sizeof(char *);
	row_size = cols * sizeof(char);

	*map = malloc(pointers_size + (rows * row_size));
	if (!(*map))
		return (-1);
	cur_row = (char *)(*map) + pointers_size;
	i = 0;
	while (i < rows)
	{
		(*map)[i] = cur_row;
		cur_row += row_size;
		i++;
	}
	return (0);
}

int allocate_game_map(t_map *map, char *raw_map_string)
{
	size_t	total_size;
	char	*data;

	total_size = map->size[y] * map->size[x];
	allocate_contiguous_map(&map->grid,
							map->size[x],
							map->size[y]);
	data = (char *)map->grid + (map->size[y] * sizeof(char *));

	ft_memset(data, ' ', total_size);
	fill_grid_from_map_string(map, raw_map_string);
	return (0);
}
