/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:29:30 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/11 19:56:55 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

int	itoa_buf(float n, char *buf)
{
	int	i;
	int	digit;

	i = 0;
	while (i < 5)
	{
		n *= 10;
		if (n == 0.0)
			break ;
		digit = (int)n;
		buf[i] = digit + '0';
		i++;
	}
	return (i);
}

int	float_to_char(float n, char *buf)
{
	float	float_int_part;
	float	float_dec_part;
	int		int_part;
	int		i;

	i = 0;
	if (n < 0)
		n = -n;
	int_part = (int)n;
	float_dec_part = n - int_part;
	float_int_part = n - float_dec_part; 
	i = itoa_buf(float_int_part, buf);
	buf[i++] = '.';
	i = itoa_buf(float_dec_part, buf + i);
	return (i);
}

int	log_param_to_buf(char *key, float value, char *buf)
{
	int	i;

	i = 0;
	while (*key)
		buf[i++] = *key++;
	buf[i++] = ':';
	buf[i++] = ' ';
	i = float_to_char(value, buf + i);
	buf[i] = ' ';
	buf[i + 1] = '|';
	buf[i + 2] = ' ';
	return (i + 3);
}

int	print_vars(t_game *g, t_render *r)
{
	char	buf[100];
	int		i;

	i = 0;
	 
	mlx_string_put(r->mlx, r->win,
			r->width * 0.03, r->height * 0.03,
			0xFFCC00,
			"");
}
