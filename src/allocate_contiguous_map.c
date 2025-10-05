/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_contiguous_map.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:41:27 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/05 22:44:00 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

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

