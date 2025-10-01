/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:30 by atran             #+#    #+#             */
/*   Updated: 2025/10/01 16:10:58 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_game	game;
	int		fd;

	fd = validate_arg(argc, argv);
	if (parse_scene(fd, &data) != 0)
	{
		free_data(&data);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	game.data = &data;
	game.big_block = WIDTH / data.map.width;
	data.map.player.x *= BLOCK;
	data.map.player.y *= BLOCK;
	data.map.player.radius = BLOCK / 20;
	init_game(&game);
	mlx_terminate(game.mlx);
	free_data(&data);
	return (0);
}
