/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:00:52 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/23 15:11:55 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	int	*pixels;

	pixels = (int *)img->addr;
	return (pixels[y * (img->size_line >> 2) + x]);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	int	*pixels;

	pixels = (int *)img->addr;
	pixels[y * (img->size_line >> 2) + x] = color;
}
