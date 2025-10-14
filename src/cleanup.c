/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:50:16 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 18:51:03 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

// config cleanup function. we can just continously add to this
// as elements in the struct increase.
//
static void	cleanup_config(t_config *config)
{
	if (!config)
		return ;
	free(config->tex_no);
	free(config->tex_so);
	free(config->tex_ea);
	free(config->tex_we);
}

static void	cleanup_map(t_map *map)
{
	if (!map)
		return ;
	free(map->grid);
}

void	cleanup_all(t_game *game)
{
	if (!game)
		return ;
	cleanup_config(&game->config);
	cleanup_map(&game->map);
	cleanup_window(&game->win);
}
