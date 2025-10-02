/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:05 by atran             #+#    #+#             */
/*   Updated: 2025/10/02 10:45:23 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_block(t_block *block, uint32_t color, t_game *game)
{
	int	i;

	i = 0;
	while (i < block->size)
	{
		mlx_put_pixel(game->mini_map, block->x + i, block->y, color);
		mlx_put_pixel(game->mini_map, block->x + i, block->y + block->size,
			color);
		mlx_put_pixel(game->mini_map, block->x, block->y + i, color);
		mlx_put_pixel(game->mini_map, block->x + block->size, block->y + i,
			color);
		i++;
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			mlx_put_pixel(game->mini_map, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game, char **map)
{
	int		i;
	int		j;
	t_block	block;

	i = 0;
	block.size = game->minimap_scale;
	draw_background(game);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				block.x = j * block.size;
				block.y = i * block.size;
				draw_block(&block, 0x0000FFFF, game);
			}
			j++;
		}
		i++;
	}
}

void	draw_ray_2d(t_coords *player, t_game *game, float start_x)
{
	float	ray_x;
	float	ray_y;
	int		minimap_x;
	int		minimap_y;

	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game->data->map))
	{
		minimap_x = (ray_x / BLOCK) * game->minimap_scale;
		minimap_y = (ray_y / BLOCK) * game->minimap_scale;
		if (minimap_x >= 0 && minimap_x < MINIMAP_WIDTH && minimap_y >= 0
			&& minimap_y < MINIMAP_HEIGHT)
			mlx_put_pixel(game->mini_map, minimap_x, minimap_y, 0xFF0000FF);
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
}

void	draw_2d_player(t_game *game)
{
	t_coords	*player;
	t_block		pl_block;

	player = &game->data->map.player;
	pl_block.x = (player->x / BLOCK) * game->minimap_scale;
	pl_block.y = (player->y / BLOCK) * game->minimap_scale;
	pl_block.size = 2;
	draw_block(&pl_block, 0xFF0000FF, game);
}
