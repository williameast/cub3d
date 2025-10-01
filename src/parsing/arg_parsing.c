/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:31:20 by weast             #+#    #+#             */
/*   Updated: 2025/09/09 16:53:55 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

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

int	validate_filename(char *filename);


char *read_map(char *filename)
{
	int	fd;
	char *map_string;
	char *line;
	char *temp;

	fd = open(filename, O_RDONLY);
	map_string = NULL;
	if (fd < 0 || !check_extension(filename))
		return (NULL);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (map_string == NULL)
			map_string = ft_strdup(line);
		else
		{
			temp = ft_strjoin(map_string, line);
			free(map_string);
			map_string = temp;
		}
		free(line);
	}
	close(fd);
	return (map_string);
}
