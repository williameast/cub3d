/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:36:09 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/14 18:15:28 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/unity/src/unity.h"
#include "../include/cub3d.h"

void	test_valid_map_is_created(char *map)
{
	t_game	game = {0};
	int		ret;

	ret = parse_map(&game, map);
	TEST_ASSERT_EQUAL(ret, OK);
	TEST_ASSERT_NOT_EQUAL(game.map.grid, NULL);
	TEST_ASSERT(game.map.size[x] > 0);
	TEST_ASSERT(game.map.size[y] > 0);
	cleanup_all(&game);
}

void	test_invalid_map_is_not_created(char *map)
{
	t_game	game = {0};
	int		ret;

	ret = parse_map(&game, map);
	TEST_ASSERT_EQUAL(ret, ERR);
	TEST_ASSERT_NOT_EQUAL(game.map.grid, NULL);
	TEST_ASSERT(game.map.size[x] = 0);
	TEST_ASSERT(game.map.size[y] = 0);
	cleanup_all(&game);
}

void	test_valid_maps(void)
{
	char	*valid_maps[] = {
		"../maps/testing/valid/long_corridor.cub",
		"../maps/testing/valid/map1.cub",
		"../maps/testing/valid/minimal.cub",
		"../maps/testing/valid/offset_map.cub",
	};
	int		n_maps;
	int		i;

	n_maps = 4;
	i = 0;
	while (i < n_maps)
		test_valid_map_is_created(valid_maps[i]);
}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_valid_maps);
	return UNITY_END();
}
