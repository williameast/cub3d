/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/10/02 12:55:11 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_window *window)
{
	window->width = WIDTH;
	window->height = HEIGHT;
	window->mlx = mlx_init(window->width,
						   window->height,
						   WIN_NAME, false);
	if (!window->mlx)
		return (1);
	window->img = mlx_new_image(window->mlx,
								window->width,
								window->height);
	if (!window->img)
	{
		mlx_terminate(window->mlx);
		return (1);
	}
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) < 0)
	{
		mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
		return (1);
	}
	return (0);
}

void	cleanup_window(t_window *window)
{
	if (window->img)
		mlx_delete_image(window->mlx, window->img);
	if (window->mlx)
		mlx_terminate(window->mlx);
	free(window->mlx);
}
