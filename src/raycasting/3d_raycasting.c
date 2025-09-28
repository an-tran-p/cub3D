#include "cub3d.h"

void	distance_to_next_grid(t_ray *ray, t_coords *player, float *dis_grid_x,
		float *dis_grid_y)
{
	// Step direction along X
	if (cos(ray->angle) < 0)
	{
		ray->step_x = -1;
		*dis_grid_x = player->x - (int)player->x;
	}
	else
	{
		ray->step_x = 1;
		*dis_grid_x = ((int)player->x + 1) - player->x;
	}
	// Step direction along Y
	if (sin(ray->angle) < 0)
	{
		ray->step_y = -1;
		*dis_grid_y = player->y - (int)player->y;
	}
	else
	{
		ray->step_y = 1;
		*dis_grid_y = ((int)player->y + 1) - player->y;
	}
	// Normalize by ray direction
	*dis_grid_x = *dis_grid_x / fabs(cos(ray->angle));
	*dis_grid_y = *dis_grid_y / fabs(sin(ray->angle));
}

void	calculate_distance_to_wall(t_ray *ray, t_coords *player, t_game *game)
{
	int		map_x;
	int		map_y;
	float	dis_grid_x;
	float	dis_grid_y;

	map_x = (int)player->x;
	map_y = (int)player->y;
	dis_grid_x = 0;
	dis_grid_y = 0;
	distance_to_next_grid(ray, player, &dis_grid_x, &dis_grid_y);
	// DDA loop
	ray->wall = VERTICAL_WALL;
	while (!touch(map_x, map_y, game->data->map))
	{
		if (dis_grid_x < dis_grid_y)
		{
			dis_grid_x = dis_grid_x + fabs(1 / cos(ray->angle));
			map_x = map_x + ray->step_x;
			ray->wall = VERTICAL_WALL;
		}
		else
		{
			dis_grid_y = dis_grid_y + fabs(1 / sin(ray->angle));
			map_y = map_y + ray->step_y;
			ray->wall = HORIZONTAL_WALL;
		}
	}
	// Perpendicular distance to wall
	if (ray->wall == VERTICAL_WALL)
		ray->dist = (map_x - player->x + (1 - ray->step_x) / 2.0f)
			/ cos(ray->angle);
	else
		ray->dist = (map_y - player->y + (1 - ray->step_y) / 2.0f)
			/ sin(ray->angle);
}

t_ray	casting_ray(t_coords *player, t_game *game, float start_x)
{
	t_ray	ray;

	ray.angle = start_x;
	calculate_distance_to_wall(&ray, player, game);
	ray.ray_x = player->x + cos(ray.angle) * ray.dist;
	ray.ray_y = player->y + sin(ray.angle) * ray.dist;
	ray.height = (BLOCK * (WIDTH / 2) / tan((M_PI / 3) / 2)) / ray.dist;
	ray.start_y = (HEIGHT - ray.height) / 2;
	if (ray.start_y < 0)
		ray.start_y = 0;
	ray.end = ray.start_y + ray.height;
	if (ray.wall == VERTICAL_WALL)
	{
		ray.side = EAST;
		if (cos(ray.angle) > 0)
			ray.side = WEST;
	}
	else
	{
		if (sin(ray.angle) > 0)
			ray.side = NORTH;
		else
			ray.side = SOUTH;
	}
	return (ray);
}

void	view_3d(t_coords *player, t_game *game, float start_x, int i)
{
	t_ray	ray;
	int		y;

	// Draw ceiling (top to wall start)
	ray = casting_ray(player, game, start_x);
	y = -1;
	while (y++ < ray.start_y)
		mlx_put_pixel(game->image, i, y, game->data->c_color);
	while (ray.start_y < ray.end && ray.start_y < HEIGHT)
	{
		if (ray.side == NORTH)
			mlx_put_pixel(game->image, i, ray.start_y, 0x0000FFFF);
		if (ray.side == SOUTH)
			mlx_put_pixel(game->image, i, ray.start_y, 0x00FF00FF);
		if (ray.side == EAST)
			mlx_put_pixel(game->image, i, ray.start_y, 0xFF0000FF);
		if (ray.side == WEST)
			mlx_put_pixel(game->image, i, ray.start_y, 0xFFFF00FF);
		ray.start_y++;
	}
	// Draw floor (wall end to bottom)
	y = ray.end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->image, i, y, game->data->f_color);
		y++;
	}
}

void	render_frame(t_game *game)
{
	float		fraction;
	float		start_x;
	t_coords	*player;
	int			i;
	int			max;

	player = &game->data->map.player;
	fraction = M_PI / 3 / (game->data->map.width * BLOCK);
	start_x = player->angle - M_PI / 6;
	i = 0;
	if (game->data->map.width * BLOCK < WIDTH)
		max = game->data->map.width * BLOCK;
	else
		max = WIDTH;
	while (i < max)
	{
		if (CUB2D)
			draw_ray_2d(player, game, start_x);
		if (!CUB2D)
			view_3d(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
}
