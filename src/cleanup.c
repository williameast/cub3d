/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:50:16 by weast             #+#    #+#             */
/*   Updated: 2025/10/06 17:07:08 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


// config cleanup function. we can just continously add to this
// as elements in the struct increase.
//
void	cleanup_config(t_config *config)
{
	if (!config)
		return ;
	free(config->raw_file_string);
	free(config->tex_no);
	free(config->tex_so);
	free(config->tex_ea);
	free(config->tex_we);
	free(config->col_floor_raw);
	free(config->col_ceiling_raw);
}

void	cleanup_map(t_map *map)
{
	free(map->grid);
}
