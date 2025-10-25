/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:35:00 by weast             #+#    #+#             */
/*   Updated: 2025/10/23 22:08:43 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	extract_rgb(char *line, int skip)
{
	int		i;
	int		rgb;
	char	**split;
	char	*temp;
	int		colors[3];

	temp = extract_value(line, skip);
	split = ft_split(temp, ',');
	free(temp);
	i = 0;
	rgb = 0;
	while (split[i] != NULL && i < 3)
	{
		colors[i] = ft_atoi(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	if (i == 3)
		rgb = (colors[0] << 16) | (colors[1] << 8) | colors[2];
	return (rgb);
}

static void	store_line_value(t_line_id id, t_config *config, char *line)
{
	if (id == LINE_NO)
		config->tex_path[NORTH] = extract_value(line, 2);
	else if (id == LINE_SO)
		config->tex_path[SOUTH] = extract_value(line, 2);
	else if (id == LINE_WE)
		config->tex_path[WEST] = extract_value(line, 2);
	else if (id == LINE_EA)
		config->tex_path[EAST] = extract_value(line, 2);
	else if (id == LINE_F)
		config->col_floor = extract_rgb(line, 1);
	else if (id == LINE_C)
		config->col_ceiling = extract_rgb(line, 1);
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
		store_line_value(id, config, line);
		if (*str == '\n')
			str++;
	}
	return (OK);
}
