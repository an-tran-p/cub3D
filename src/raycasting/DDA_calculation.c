/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:41:04 by atran             #+#    #+#             */
/*   Updated: 2025/10/02 11:04:19 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	distance_to_next_grid(t_ray *ray, t_coords *player, float *dis_grid_x,
		float *dis_grid_y)
{
	*dis_grid_x = 0;
	*dis_grid_y = 0;
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
	*dis_grid_x = *dis_grid_x / fabs(cos(ray->angle));
	*dis_grid_y = *dis_grid_y / fabs(sin(ray->angle));
}

void	calculate_ray_dist(t_coords *player, int map_x, int map_y, t_ray *ray)
{
	if (ray->wall == VERTICAL_WALL)
		ray->dist = (map_x - player->x + (1 - ray->step_x) / 2.0f)
			/ cos(ray->angle);
	else
		ray->dist = (map_y - player->y + (1 - ray->step_y) / 2.0f)
			/ sin(ray->angle);
	if (ray->dist < 0.0001)
		ray->dist = 0.001;
}

void	calculate_distance_to_wall(t_ray *ray, t_coords *player, t_game *game)
{
	int		map_x;
	int		map_y;
	float	dis_grid_x;
	float	dis_grid_y;

	map_x = (int)player->x;
	map_y = (int)player->y;
	distance_to_next_grid(ray, player, &dis_grid_x, &dis_grid_y);
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
	calculate_ray_dist(player, map_x, map_y, ray);
}

void	set_wall_side(t_ray *ray)
{
	if (ray->wall == VERTICAL_WALL)
	{
		ray->side = WEST;
		if (cos(ray->angle) > 0)
			ray->side = EAST;
	}
	else
	{
		if (sin(ray->angle) > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
}

t_ray	casting_ray(t_coords *player, t_game *game, float start_x)
{
	t_ray	ray;

	ft_memset(&ray, 0, sizeof(t_ray));
	ray.angle = start_x;
	calculate_distance_to_wall(&ray, player, game);
	ray.ray_x = player->x + cos(ray.angle) * ray.dist;
	ray.ray_y = player->y + sin(ray.angle) * ray.dist;
	ray.height = (BLOCK * (WIDTH / 2) / tan((M_PI / 3) / 2)) / (ray.dist
			* cos(ray.angle - player->angle));
	ray.start_y = (HEIGHT - ray.height) / 2;
	if (ray.start_y < 0)
		ray.start_y = 0;
	ray.end = ray.start_y + ray.height;
	set_wall_side(&ray);
	return (ray);
}
