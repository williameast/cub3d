/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:25:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/21 22:52:07 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

int	render_frame(void *arg)
{
	t_game	*game;

	game = arg;
	raycasting(game);
	return (OK);
}
