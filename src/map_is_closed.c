/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/14 11:36:10 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

int	is_closed(int Y, int X, t_map *map, char **visited);

int	is_edge(int Y, int X, t_map *map)
{
	if (Y == 0 || Y == map->size[y] - 1
		|| X == 0 || X == map->size[x] - 1)
		return (1);
	return (0);
}

int	is_invalid(int Y, int X, t_map *map, char **visited)
{
	if ((map->grid[Y][X] == '1')
		|| (visited[Y][X]))
		return (0);
	visited[Y][X] = '1';
	if ((is_edge(Y, X, map)
			|| !is_closed(Y, X, map, visited)))
		return (1);
	return (0);
}

int	is_closed(int Y, int X, t_map *map, char **visited)
{
	if ((is_invalid(Y - 1, X, map, visited))
		|| (is_invalid(Y + 1, X, map, visited))
		|| (is_invalid(Y, X - 1, map, visited))
		|| (is_invalid(Y, X + 1, map, visited)))
		return (0);
	return (1);
}

int	map_is_closed(t_map *map, double *player, t_game *game)
{
	char	**visited;

	if (OK != allocate_contiguous_map(&visited, map->size[x], map->size[y]))
		return (handle_error("Error: map_is_closed: malloc fail", game , ERR));
	ft_memset(*visited, 0, map->size[y] * map->size[x]);
	find_player(map->grid, player, map->size[x], map->size[y]);
	if (!is_closed(player[y], player[x], map, visited))
		return (handle_error("Error: map_is_closed: map not closed", game, INVALID));
	return (free(visited), OK);
}
