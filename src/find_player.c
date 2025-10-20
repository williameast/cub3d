/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:26:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/20 13:57:42 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "libft.h"

void	find_player(char **map, double *player, int cols, int rows)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < rows)
	{
		while (col < cols)
		{
			if (ft_strchr(MAP_VALID_PLAYER_CHARS, map[row][col]))
			{
				player[y] = row;
				player[x] = col;
				return ;
			}
			col++;
		}
		col = 0;
		row++;
	}
}


// right now I have made a bit more defensively coded
// to check also bounds. but we can probably take that out.
int	validate_player_move(t_map *map, double pos[2])
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)pos[x];
	grid_y = (int)pos[y];
	if (grid_x < 0 || grid_x >= map->size[x])
		return (INVALID);
	if (grid_y < 0 || grid_y >= map->size[y])
		return (INVALID);
	if (map->grid[grid_y][grid_x] == '1')
		return (INVALID);
	return (OK);
}
