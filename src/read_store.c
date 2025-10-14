/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:35:00 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 17:35:00 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	store_line_value(t_line_id id, t_parse *parse, t_config *config, \
				char *line)
{
	if (id == LINE_NO)
		config->tex_no = extract_value(line, 2);
	else if (id == LINE_SO)
		config->tex_so = extract_value(line, 2);
	else if (id == LINE_WE)
		config->tex_we = extract_value(line, 2);
	else if (id == LINE_EA)
		config->tex_ea = extract_value(line, 2);
	else if (id == LINE_F)
		parse->raw_col_floor = extract_value(line, 1);
	else if (id == LINE_C)
		parse->raw_col_ceiling = extract_value(line, 1);
}

int	store_config_values(t_parse *parse, t_config *config)
{
	char		*str;
	char		*line;
	t_line_id	id;

	str = parse->raw_file_string;
	while (*str)
	{
		line = str;
		while (*str && *str != '\n')
			str++;
		id = return_line_identifier(line);
		if (id == LINE_MAP)
			break ;
		store_line_value(id, parse, config, line);
		if (*str == '\n')
			str++;
	}
	return (0);
}
