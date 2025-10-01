#include "cub3d.h"

void	draw_block(int x, int y, int size, uint32_t color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(game->mini_map, x + i, y, color);
		mlx_put_pixel(game->mini_map, x + i, y + size, color);
		mlx_put_pixel(game->mini_map, x, y + i, color);
		mlx_put_pixel(game->mini_map, x + size, y + i, color);
		i++;
	}
}

void	draw_map(t_game *game, char **map)
{
	int	i;
	int	j;
	int	block;

	i = 0;
	block = game->minimap_scale;
	for (int y = 0; y < MINIMAP_HEIGHT; y++)
	{
		for (int x = 0; x < MINIMAP_WIDTH; x++)
			mlx_put_pixel(game->mini_map, x, y, 0x00000000);
	}
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_block(j * block, i * block, block, 0x0000FFFF, game);
			j++;
		}
		i++;
	}
}

bool	touch(float px, float py, t_map map)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y < 0 || y >= map.height || x < 0 || x >= map.width)
		return (true);
	if (map.map_data[y][x] == '1')
		return (true);
	return (false);
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
