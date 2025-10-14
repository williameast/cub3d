/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:40:00 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 17:40:00 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	validate_all_counts(int counts[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (counts[i] != 1)
			return (-1);
		i++;
	}
	return (0);
}

static int	process_config_line(t_line_id id, int counts[6])
{
	if (id == LINE_NO && increment_and_check(&counts[0]) == -1)
		return (-1);
	if (id == LINE_SO && increment_and_check(&counts[1]) == -1)
		return (-1);
	if (id == LINE_WE && increment_and_check(&counts[2]) == -1)
		return (-1);
	if (id == LINE_EA && increment_and_check(&counts[3]) == -1)
		return (-1);
	if (id == LINE_F && increment_and_check(&counts[4]) == -1)
		return (-1);
	if (id == LINE_C && increment_and_check(&counts[5]) == -1)
		return (-1);
	return (0);
}

int	check_config_is_valid(t_parse *parse)
{
	int			counts[6];
	char		*line;
	char		*str;
	t_line_id	id;

	if (!parse || !parse->raw_file_string)
		return (-1);
	ft_memset(counts, 0, sizeof(counts));
	str = parse->raw_file_string;
	while (*str)
	{
		line = str;
		while (*str && *str != '\n')
			str++;
		id = return_line_identifier(line);
		if (id == LINE_MAP)
			break ;
		if (process_config_line(id, counts) == -1)
			return (-1);
		if (*str == '\n')
			str++;
	}
	return (validate_all_counts(counts));
}

int	return_offset(t_parse *parse)
{
	char		*str;
	char		*line;
	int			offset;
	t_line_id	id;

	if (!parse || !parse->raw_file_string)
		return (-1);
	str = parse->raw_file_string;
	offset = 0;
	while (*str)
	{
		line = str;
		while (*str && *str != '\n')
			str++;
		id = return_line_identifier(line);
		if (id == LINE_MAP)
			return (offset);
		if (*str == '\n')
			str++;
		offset = str - parse->raw_file_string;
	}
	return (-1);
}
