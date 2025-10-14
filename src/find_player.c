/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:26:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/14 18:50:57 by weast            ###   ########.fr       */
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
