/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:20:01 by weast             #+#    #+#             */
/*   Updated: 2025/10/20 12:42:23 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_window *window)
{
	if (!window)
		return (1);
	window->width = WIDTH;
	window->height = HEIGHT;
	window->mlx = mlx_init();
	if (!window->mlx)
		return (1);
	window->win = mlx_new_window(window->mlx, window->width,
			window->height, WIN_NAME);
	if (!window->win)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
		return (1);
	}
	window->img = mlx_new_image(window->mlx, window->width, window->height);
	if (!window->img)
	{
		mlx_destroy_window(window->mlx, window->win);
		mlx_destroy_display(window->mlx);
		free(window->mlx);
		return (1);
	}
	window->img_data = mlx_get_data_addr(window->img, &window->bits_per_pixel,
			&window->size_line, &window->endian);
	return (0);
}

void	cleanup_window(t_window *window)
{
	if (window->img)
		mlx_destroy_image(window->mlx, window->img);
	window->img = NULL;
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	window->win = NULL;
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	window->mlx = NULL;
}
