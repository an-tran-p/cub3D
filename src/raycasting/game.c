#include "cub3d.h"

bool	touch(float px, float py, char **map)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (map[y][x] == '1')
		return (true);
	return (false);
}

void	draw_block(int x, int y, int size, uint32_t color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mlx_put_pixel(game->image, x + i, y, color);
		mlx_put_pixel(game->image, x + i, y + size, color);
		mlx_put_pixel(game->image, x, y + i, color);
		mlx_put_pixel(game->image, x + size, y + i, color);
		i++;
	}
}

void	draw_map(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_block(j * BLOCK, i * BLOCK, BLOCK, 0x0000FFFF, game);
			j++;
		}
		i++;
	}
}

void	draw_ray_2d(t_coords *player, t_game *game, float start_x)
{
	float	ray_x;
	float	ray_y;

	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game->data->map.map_data))
	{
		mlx_put_pixel(game->image, (int)ray_x, (int)ray_y, 0x00FF00FF);
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->data->map.player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	view_3d(t_coords *player, t_game *game, float start_x, int i)
{
	float	dist;
	float	height;
	int		start_y;
	int		end;
	float	ray_x;
	float	ray_y;

	ray_x = player->x;
	ray_y = player->y;
	while (!touch(ray_x, ray_y, game->data->map.map_data))
	{
		ray_x += cos(start_x);
		ray_y += sin(start_x);
	}
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	height = (BLOCK / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	while (start_y < end)
	{
		mlx_put_pixel(game->image, i, start_y, 0x0000FFFF);
		start_y++;
	}
}

void	casting_ray(t_game *game)
{
	float		fraction;
	float		start_x;
	t_coords	*player;
	int			i;

	player = &game->data->map.player;
	fraction = M_PI / 3 / (31 * BLOCK);
	start_x = player->angle - M_PI / 6;
	i = 0;
	while (i < 31 * BLOCK)
	{
		if (CUB2D)
			draw_ray_2d(player, game, start_x);
		if (!CUB2D)
			view_3d(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
}

void	init_game(t_game *game, t_coords *player)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		return ;
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return ;
	if (CUB2D)
	{
		draw_block(player->x, player->y, BLOCK, 0xFF0000FF, game);
		draw_map(game, game->data->map.map_data);
	}
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	mlx_key_hook(game->mlx, handle_keyhook, player);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
