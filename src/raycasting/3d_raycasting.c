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

void	put_wall_texture(t_ray *ray, t_game *game, int y, int i)
{
	int			d;
	float		wall_x;
	int			tex_x;
	int			tex_y;
	uint32_t	pixel_color;

	// calculate x coordinate in the wall
	if (ray->side == NORTH || ray->side == SOUTH)
		wall_x = fmod(ray->ray_x, BLOCK) / (float)BLOCK;
	else
		wall_x = fmod(ray->ray_y, BLOCK) / (float)BLOCK;
	// calculate x coordinate in texture
	tex_x = (int)(wall_x * (float)game->tex_size);
	// calculate corresponding y in the texture
	d = y - ray->start_y;
	tex_y = (int)((float)d / ray->height * game->tex_size);
	// get pixel clor from x & y coordinate in the texture
	if (ray->side == NORTH)
		pixel_color = ((uint32_t *)game->no_wall->pixels)[tex_y * game->tex_size
			+ tex_x];
	else if (ray->side == SOUTH)
		pixel_color = ((uint32_t *)game->so_wall->pixels)[tex_y * game->tex_size
			+ tex_x];
	else if (ray->side == EAST)
		pixel_color = ((uint32_t *)game->ea_wall->pixels)[tex_y * game->tex_size
			+ tex_x];
	else
		pixel_color = ((uint32_t *)game->we_wall->pixels)[tex_y * game->tex_size
			+ tex_x];
	pixel_color = pixel_color | 0xFF000000;
	mlx_put_pixel(game->image, i, y, pixel_color);
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
	y = ray.start_y;
	while (y < ray.end && y < HEIGHT)
	{
		put_wall_texture(&ray, game, y, i);
		y++;
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
