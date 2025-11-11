/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:00:52 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/11 18:43:08 by weast            ###   ########.fr       */
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

static void	draw_map_tiles(t_game *game)
{
	int scale;
	int offset_x;
	int offset_y;
	int map_x;
	int map_y;

	scale = 10;
	offset_x = 10;
	offset_y = 10;
	map_y = 0;
	while (map_y < game->map.size[y])
	{
		map_x = 0;
		while (map_x < game->map.size[x])
		{
			if (game->map.grid[map_y][map_x] == '1')
				draw_square(game->render.back, offset_x + map_x * scale,
					offset_y + map_y * scale, scale, 0xFFFFFF);
			map_x++;
		}
		map_y++;
	}
}

static void	draw_player(t_game *game)
{
	int	scale;
	int	offset_x;
	int	offset_y;
	int	player_size;
	int	player_x;
	int	player_y;

	scale = 10;
	offset_x = 10;
	offset_y = 10;
	player_size = 4;
	player_x = offset_x + (int)(game->player.pos[x] * scale) - player_size / 2;
	player_y = offset_y + (int)(game->player.pos[y] * scale) - player_size / 2;
	draw_square(game->render.back, player_x, player_y, player_size, 0xFF0000);
}

void	draw_minimap(t_game *game)
{
	draw_map_tiles(game);
	draw_player(game);
}
