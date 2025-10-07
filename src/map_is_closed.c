/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/07 13:34:37 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	is_player_direction(char c)
{
	char	*player_directions = "NSEW";
	char	*dir;

	dir = player_directions;
	while (*dir)
	{
		if (c == *dir)
			return (0);
		dir++;
	}
}

int	find_player(char **map, t_crd *player, size_t cols, size_t rows)
{
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	while (row < rows)
	{
		while (col < cols)
		{
			if (is_player_direction(map[row][col++]))
			{
				player->y = row;
				player->x = col;
			}
		}
	}
	return (-1);
}

int	map_is_closed(char **map, size_t cols, size_t rows)
{
	char	**visited;
	t_crd	player;
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	find_player(map, &player, cols, rows);
	if (OK != allocate_contiguous_map(&visited, cols, rows))
		return (perror("Error\nMalloc visited array in validaton:"), ERR);
	if (OK != find_player(map, &player, cols, rows))
		return (perror("Error\nMap with no player"), ERR);
	while (row < rows)
	{
		while (col < cols)
		{
			if (map[row][col])
		}
		col++;
	}
}
