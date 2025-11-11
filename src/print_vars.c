/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:29:30 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/12 00:04:24 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

int	itoa_buf(int n, char *buf, int skip_leading_zeros)
{
	int	divisor;
	int	digit;
	int	len;

	if (skip_leading_zeros && n == 0)
		return (buf[0] = '0', 1);
	len = 0;
	divisor = 10000;
	if (skip_leading_zeros)
		while (divisor > 0 && n < divisor)
			divisor /= 10;
	while (divisor > 0)
	{
		digit = n / divisor;
		buf[len++] = digit + '0';
		n -= digit * divisor;
		divisor /= 10;
	}
	return (len);
}

int	float_to_char(float n, char *buf)
{
	int		int_part;
	int		dec_part;
	int		i;

	i = 0;
	if (n < 0)
	{
		buf[i++] = '-';
		n = -n;
	}
	int_part = (int)n;
	dec_part = (int)((n - int_part) * 100000);
	i += itoa_buf(int_part, buf + i, 1);
	buf[i++] = '.';
	i += itoa_buf(dec_part, buf + i, 0);
	return (i);
}

int	write_string_to_buf(char *str, char *buf)
{
	int	i;

	i = 0;
	while (str[i])
	{
		buf[i] = str[i];
		i++;
	}
	return (i);
}

int	log_param_to_buf(char *key, float value, char *buf)
{
	int	i;

	i = 0;
	while (*key)
		buf[i++] = *key++;
	buf[i++] = ':';
	i += float_to_char(value, buf + i);
	buf[i++] = ' ';
	return (i);
}

// Main debug function with titles
void	print_debug_vars(t_game *g)
{
	char	buf[512];
	int		i;

	// Line 1: PLAYER
	i = 0;
	i += write_string_to_buf("PLAYER: ", buf + i);
	i += log_param_to_buf("x:", (float)g->player.pos[x], buf + i);
	i += log_param_to_buf("y:", (float)g->player.pos[y], buf + i);
	i += log_param_to_buf("angle:", g->player.angle, buf + i);
	buf[i] = '\0';
	mlx_string_put(g->render.mlx, g->render.win, 10, 20, 0x00FF00, buf);
	// Line 2: MAP
	i = 0;
	i += write_string_to_buf("MAP: ", buf + i);
	i += log_param_to_buf("width:", (float)g->map.size[x], buf + i);
	i += log_param_to_buf("height:", (float)g->map.size[y], buf + i);
	buf[i] = '\0';
	mlx_string_put(g->render.mlx, g->render.win, 10, 40, 0x00FF00, buf);
}
