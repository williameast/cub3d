/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:30:00 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 18:28:34 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int	increment_and_check(int *counter)
{
	(*counter)++;
	if (*counter > 1)
		return (ERR);
	return (OK);
}

char	*extract_value(char *line, int skip)
{
	char	*start;
	char	*end;
	int		len;

	start = line;
	while (*start == ' ' || *start == '\t')
		start++;
	start += skip;
	while (*start == ' ' || *start == '\t')
		start++;
	end = start;
	while (*end && *end != '\n')
		end++;
	while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
		end--;
	len = end - start;
	return (ft_substr(start, 0, len));
}

static int	check_texture_line(char *line, int i, int is_two_char)
{
	if (is_two_char)
	{
		if (!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "NO\t", 3))
			return (LINE_NO);
		if (!ft_strncmp(&line[i], "SO ", 3) || !ft_strncmp(&line[i], "SO\t", 3))
			return (LINE_SO);
		if (!ft_strncmp(&line[i], "WE ", 3) || !ft_strncmp(&line[i], "WE\t", 3))
			return (LINE_WE);
		if (!ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i], "EA\t", 3))
			return (LINE_EA);
	}
	else
	{
		if (!ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "F\t", 2))
			return (LINE_F);
		if (!ft_strncmp(&line[i], "C ", 2) || !ft_strncmp(&line[i], "C\t", 2))
			return (LINE_C);
	}
	return (LINE_INVALID);
}

t_line_id	return_line_identifier(char *line)
{
	int			i;
	t_line_id	result;

	if (!line)
		return (LINE_INVALID);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (LINE_EMPTY);
	if (line[0] == '1' || line[0] == ' ')
		return (LINE_MAP);
	result = check_texture_line(line, i, 1);
	if (result != LINE_INVALID)
		return (result);
	return (check_texture_line(line, i, 0));
}

void	cleanup_parse(t_parse *parse)
{
	if (!parse)
		return ;
	free(parse->raw_file_string);
	free(parse->raw_col_floor);
	free(parse->raw_col_ceiling);
}
