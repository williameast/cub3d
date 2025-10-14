/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:26:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/14 13:48:53 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	is_player_direction(char c)
{
	char	*dir;

	dir = PLAYER_DIRECTIONS;
	while (*dir)
	{
		if (c == *dir)
			return (c);
		dir++;
	}
	return (0);
}

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
			if (is_player_direction(map[row][col]))
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
