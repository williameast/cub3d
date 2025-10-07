/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/07 19:52:39 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "libft.h"

int	is_closed(int y, int x, t_map *map, char **visited);

int	is_edge(int y, int x, t_map *map)
{
	if (y == 0 || y == map->size[y] - 1
		|| x == 0 || x == map->size[x] - 1)
		return (1);
	return (0);
}

int	is_invalid(int y, int x, t_map *map, char **visited)
{
	return ((!visited[y][x]
		&& map->grid[y][x] != 1)
		&& (is_edge(y, x, map)
			|| !is_closed(y, x, map, visited)));
}

int	is_closed(int y, int x, t_map *map, char **visited)
{
	if ((is_invalid(y - 1, x, map, visited))
		|| (is_invalid(y + 1, x, map, visited))
		|| (is_invalid(y, x - 1, map, visited))
		|| (is_invalid(y, x + 1, map, visited)))
		return (0);
	return (1);
}

int	map_is_closed(t_map *map, double *player)
{
	char	**visited;

	if (OK != allocate_contiguous_map(&visited, map->size[y], map->size[x]))
		return (perror("Error\nMalloc visited array in validaton:"), ERR);
	ft_bzero(map->grid, map->size[y] * map->size[x]);
	find_player(map->grid, player, map->size[y], map->size[x]);
	if (!is_closed(player[y], player[x], map, visited))
		return (free(visited), 0);
	return (free(visited), 1);
}
