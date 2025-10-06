/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_contiguous_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:41:27 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/06 14:23:12 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

static void	fill_grid_from_map_string(t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (map->raw_map_string[i])
	{
		if (map->raw_map_string[i] == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			GRID(x, y) = map->raw_map_string[i];
			x++;
		}
		i++;
	}
}

/* Allocates a 2D char array (rows x cols) with a single malloc in contiguous memory
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
	char *	cur_row;
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

/* Allocates a flat 1D array for the map grid (rows * cols)
 * This is the most cache-friendly approach with zero pointer overhead.
 * Access pattern: map->grid[y * map->dimension.x + x]
 * I set it to ' ' as a placeholder, because that is the deadspace
 * in the beginning of rows.
 *
 * Benefits:
 *   - Single malloc, single free
 *   - No pointer indirection overhead
 *   - Best cache locality for sequential access
 *   - Optimal for tight rendering loops
 */
int	allocate_flat_map(t_map *map)
{
	size_t	total_size;

	total_size = map->dimension.y * map->dimension.x;
	map->grid = malloc(total_size * sizeof(char));
	if (!map->grid)
		return (-1);
	ft_memset(map->grid, ' ', total_size);
	fill_grid_from_map_string(map);
	return (0);
}
