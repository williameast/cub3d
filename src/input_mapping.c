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
int	key_hook(int keycode, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (keycode == 65307)
	{
		mlx_loop_end(window->mlx);
	}
	return (0);
}
