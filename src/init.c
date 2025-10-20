/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 18:50:54 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_window *window)
{
	int		x;
	int		y;

	window->width = WIDTH;
	window->height = HEIGHT;
	window->mlx = mlx_init(window->width, window->height, WIN_NAME, false);
	if (!window->mlx)
		return (1);
	window->img = mlx_new_image(window->mlx, window->width, window->height);
	if (!window->img)
	{
		mlx_terminate(window->mlx);
		return (1);
	}
	y = 0;
	while (y < window->height)
	{
		x = 0;
		while (x < window->width)
			mlx_put_pixel(window->img, x++, y, 0xFFFFFFFF);
		y++;
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
	if (!window)
		return ;
	if (window->mlx)
	{
		if (window->img)
			mlx_delete_image(window->mlx, window->img);
		mlx_terminate(window->mlx);
	}
}
