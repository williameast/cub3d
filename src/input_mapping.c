/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mapping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:25:40 by weast             #+#    #+#             */
/*   Updated: 2025/10/07 14:31:20 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this we use to handle key presses.
void	key_hook(mlx_key_data_t key_press, void *param)
{
	t_window *window = (t_window *)param;
	if (key_press.key == MLX_KEY_ESCAPE && key_press.action == MLX_PRESS)
		mlx_close_window(window->mlx);
}
