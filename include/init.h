/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:15:43 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/12 18:19:19 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct transpose {
	int	line_len_in_px_src;
	int	line_len_in_px_dst;
	int	i_px_color_src;
	int	i_px_dest;
	int	*dst_addr;
	int	*src_addr;
}	t_trans;

#endif
