/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:16 by atran             #+#    #+#             */
/*   Updated: 2025/10/01 16:10:31 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	int	map_scale_x;
	int	map_scale_y;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		error_exit_game(NULL, game);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		error_exit_game(NULL, game);
	map_scale_x = MINIMAP_WIDTH / game->data->map.width;
	map_scale_y = MINIMAP_HEIGHT / game->data->map.height;
	if (map_scale_x < map_scale_y)
		game->minimap_scale = map_scale_x;
	else
		game->minimap_scale = map_scale_y;
	game->mini_map = mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!game->mini_map)
		error_exit_game(NULL, game);
	load_and_resize_textures(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	mlx_image_to_window(game->mlx, game->mini_map, 10, 10);
	mlx_key_hook(game->mlx, handle_keyhook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
