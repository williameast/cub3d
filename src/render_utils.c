/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:00:52 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 16:30:20 by weast            ###   ########.fr       */
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

void	draw_square(t_img *img, int x, int y, int size, int colour)
{
	int i;
	int j;

	i = 0;

	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(img, x + i, y + j, colour);
			j++;
		}
		i++;
	}
}

void	draw_map_tiles(t_game *game)
{
	int scale;
	int offset_x;
	int offset_y;
	int map_x;
	int map_y;

	map_y = 0;
	while (map_y < game->map.size[y])
	{
		map_x = 0;
		while (map_x < game->map.size[x])
		{
			if (game->map.grid[map_y][map_x] == '1')
				draw_square(game->render.front, , int y, int size, int colour)

		}

	}

}


void	draw_minimap(t_game *game)
{
}
