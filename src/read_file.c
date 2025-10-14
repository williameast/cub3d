/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:12:48 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 17:06:46 by weast            ###   ########.fr       */
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
		return (0);
	return (!ft_strncmp(FILE_EXT, &filename[name_len - ext_len], 5));
}

int	read_file_as_string(t_parse *parse, char *filename)
{
	int	fd;
	char *line;
	char *temp;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || !check_extension(filename))
		return (1);
	parse->raw_file_string = ft_strdup("");
	if (!parse->raw_file_string)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = ft_strjoin(parse->raw_file_string, line);
		free(parse->raw_file_string);
		if (!temp)
		{
			free(line);
			return (1);
		}
		parse->raw_file_string = temp;
		free(line);
	}
	close(fd);
	return (0);
}

/* NO ./path_to_the_north_texture */
/* SO ./path_to_the_south_texture */
/* WE ./path_to_the_west_texture */
/* EA ./path_to_the_east_texture */

/* F 220,100,0 */
/* C 225,30,0 */

/* 1111111111111111111111111 */

// Identifies the type of line from the config file.
// Returns LINE_MAP for lines starting with ' ' or '1'
// Returns LINE_EMPTY for empty lines or lines with only whitespace
// Returns LINE_INVALID if the line doesn't match any valid identifier
static t_line_id	return_line_identifier(char *line)
{
	int	i;

	if (!line)
		return (LINE_INVALID);
	i = 0;
	// Skip leading spaces/tabs (but not for map lines)
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	// Empty line
	if (line[i] == '\0' || line[i] == '\n')
		return (LINE_EMPTY);
	// Map line (starts with '1' or has leading spaces before '1' or space)
	if (line[0] == '1' || line[0] == ' ')
		return (LINE_MAP);
	// Config identifiers
	if (!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "NO\t", 3))
		return (LINE_NO);
	if (!ft_strncmp(&line[i], "SO ", 3) || !ft_strncmp(&line[i], "SO\t", 3))
		return (LINE_SO);
	if (!ft_strncmp(&line[i], "WE ", 3) || !ft_strncmp(&line[i], "WE\t", 3))
		return (LINE_WE);
	if (!ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i], "EA\t", 3))
		return (LINE_EA);
	if (!ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "F\t", 2))
		return (LINE_F);
	if (!ft_strncmp(&line[i], "C ", 2) || !ft_strncmp(&line[i], "C\t", 2))
		return (LINE_C);
	return (LINE_INVALID);
}


// Helper to increment counter and check for duplicates
static int	increment_and_check(int *counter)
{
	(*counter)++;
	if (*counter > 1)
		return (-1);
	return (0);
}

// Validates that all config fields are present exactly once
// Returns -1 if duplicates found or fields missing, 0 otherwise
int	check_config_is_valid(t_parse *parse)
{
	int			counts[6] = {0};
	char		*line;
	char		*str;
	t_line_id	id;

	if (!parse || !parse->raw_file_string)
		return (-1);
	str = parse->raw_file_string;
	while (*str)
	{
		line = str;
		while (*str && *str != '\n')
			str++;
		id = return_line_identifier(line);
		if (id == LINE_MAP)
			break;
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
		if (*str == '\n')
			str++;
	}
	for (int i = 0; i < 6; i++)
	{
		if (counts[i] != 1)
			return (-1);
	}
	return (0);
}

// Extracts the value from a config line, skipping whitespace
// Returns pointer to the start of the value (trims trailing newline)
static char	*extract_value(char *line, int skip)
{
	char	*start;
	char	*end;
	int		len;

	// Skip identifier and whitespace
	start = line;
	while (*start == ' ' || *start == '\t')
		start++;
	start += skip;
	while (*start == ' ' || *start == '\t')
		start++;
	// Find end (newline or null)
	end = start;
	while (*end && *end != '\n')
		end++;
	// Trim trailing whitespace
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	len = end - start;
	return (ft_substr(start, 0, len));
}

// Stores the config values in the t_config structure
// Returns -1 on allocation failure, 0 on success
static int	store_config_values(t_parse *parse, t_config *config)
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
			break;
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
		if (*str == '\n')
			str++;
	}
	return (0);
}

// Returns the byte offset to the first line of the map object
// Returns -1 if no map is found
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

// Parses config file and returns byte offset to map section
// Returns -1 on error (file read error, invalid config, missing fields)
int	parse_config_data(t_parse *parse, t_config *config, char *filename)
{
	if (read_file_as_string(parse, filename))
		return (-1);
	if (check_config_is_valid(parse))
		return (-1);
	if (store_config_values(parse, config))
		return (-1);

	return (return_offset(parse));
}

void	cleanup_parse(t_parse *parse)
{
	if (!parse)
		return ;
	free(parse->raw_map_string);
	free(parse->raw_file_string);
	free(parse->raw_col_floor);
	free(parse->raw_col_ceiling);
}

int	parse_map(t_game *game, char *filename)
{
	int			map_begin_offset;
	t_parse		parse = {0};

	map_begin_offset = parse_config_data(&parse, &game->config, filename);
	if (map_begin_offset == -1)
	{
		cleanup_parse(&parse);
		return(handle_error("Error: Missing or invalid config data", game));
	}
	parse.raw_map_string = parse.raw_file_string + map_begin_offset;
	if (create_map(&game->map, parse.raw_map_string))
	{
		cleanup_parse(&parse);
		return(handle_error("Error: failed to create map", game));
	}
	return (0);
}
