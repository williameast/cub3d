/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:12:48 by weast             #+#    #+#             */
/*   Updated: 2025/11/13 02:06:00 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

static int	check_extension(char *filename)
{
	int	ext_len;
	int	name_len;

	ext_len = ft_strlen(FILE_EXT);
	name_len = ft_strlen(filename);
	if (ext_len >= name_len)
		return (OK);
	return (!ft_strncmp(FILE_EXT, &filename[name_len - ext_len], 5));
}

static int	append_line_to_string(t_parse *parse, char *line)
{
	char	*temp;

	temp = ft_strjoin(parse->raw_file_string, line);
	free(parse->raw_file_string);
	if (!temp)
	{
		free(line);
		return (1);
	}
	parse->raw_file_string = temp;
	free(line);
	return (OK);
}

int	read_file_as_string(t_parse *parse, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || !check_extension(filename))
		return (ERR);
	parse->raw_file_string = ft_strdup("");
	if (!parse->raw_file_string)
		return (ERR);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (append_line_to_string(parse, line))
			return (ERR);
		line = get_next_line(fd);
	}
	close(fd);
	return (OK);
}

int	parse_config_data(t_parse *parse, t_config *config, char *filename)
{
	if (read_file_as_string(parse, filename))
		return (ERR);
	if (check_config_is_valid(parse))
		return (ERR);
	if (store_config_values(parse, config))
		return (ERR);
	return (return_offset(parse));
}

int	parse_map(t_game *game, char *filename)
{
	int		map_begin_offset;
	t_parse	parse;

	ft_memset(&parse, 0, sizeof(t_parse));
	map_begin_offset = parse_config_data(&parse, &game->config, filename);
	if (map_begin_offset == -1)
	{
		cleanup_parse(&parse);
		return (handle_error("Error: Missing or invalid config data", \
			game, INVALID));
	}
	parse.raw_map_string = parse.raw_file_string + map_begin_offset;
	if (create_map(&game->map, parse.raw_map_string, game))
	{
		cleanup_parse(&parse);
		return (handle_error("Error: failed to create map", game, INVALID));
	}
	cleanup_parse(&parse);
	debug_game(game);
	return (OK);
}
