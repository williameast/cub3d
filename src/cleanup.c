/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:50:16 by weast             #+#    #+#             */
/*   Updated: 2025/10/06 13:47:05 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


// map cleanup function. we can just continously add to this
// as elements in the struct increase.
int	cleanup_map(t_map *map)
{
	free(map->raw_map_string);
	free(map->grid);
	return 0;
}
