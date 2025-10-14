/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weast <weast@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:30:16 by weast             #+#    #+#             */
/*   Updated: 2025/10/14 17:15:46 by weast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <unistd.h>

int	handle_error(char *msg, t_game *game, int error)
{
	if (error == ERR)
		perror(msg);
	else
		ft_putstr_fd(msg, STDERR_FILENO);
	game->exit_code = error;
	return (ERR);
}
