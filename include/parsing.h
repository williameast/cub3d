/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:28:53 by weast             #+#    #+#             */
/*   Updated: 2025/09/09 16:42:25 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

# include "libft.h"
# include "fcntl.h"

#define FILE_EXT ".cub" // file extension used.


typedef struct s_map
{
	char	*map_string;
} t_map;


#endif // PARSING_H

static char	*read_full_map_as_str(char *file)
{
	int		fd;
	char	*full_line;
	char	*next_line;
	char	*temp;

	full_line = ft_strdup("");
	fd = open(file, O_RDONLY);
	if (fd < 0 || !check_extension(file, ".fdf"))
	{
		ft_printf("ERROR: <%s> is not valid or could not be found.\n", file);
		free(full_line);
		return (NULL);
	}
	next_line = get_next_line(fd);
	while (next_line != NULL)
	{
		temp = ft_strjoin(full_line, next_line);
		free(full_line);
		full_line = temp;
		free(next_line);
		next_line = get_next_line(fd);
	}
	close(fd);
	return (full_line);
}
