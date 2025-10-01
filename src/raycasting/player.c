/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:00:03 by atran             #+#    #+#             */
/*   Updated: 2025/10/01 15:00:04 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_angle_update(t_coords *player, float angle_speed)
{
	if (player->l_rotate)
		player->angle -= angle_speed;
	if (player->r_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * M_PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * M_PI;
}

void	calculate_new_xy(t_coords *player, int speed, float *new_x,
		float *new_y)
{
	if (player->up)
	{
		*new_x = player->x + cos(player->angle) * speed;
		*new_y = player->y + sin(player->angle) * speed;
	}
	if (player->down)
	{
		*new_x = player->x - cos(player->angle) * speed;
		*new_y = player->y - sin(player->angle) * speed;
	}
	if (player->left)
	{
		*new_x = player->x + sin(player->angle) * speed;
		*new_y = player->y - cos(player->angle) * speed;
	}
	if (player->right)
	{
		*new_x = player->x - sin(player->angle) * speed;
		*new_y = player->y + cos(player->angle) * speed;
	}
}

bool	is_wall_with_radius(float new_x, float new_y, t_map *map)
{
	int		check_point;
	int		check_x;
	int		check_y;
	float	angle;
	int		i;

	check_point = 8;
	i = 0;
	while (i < check_point)
	{
		angle = 2 * M_PI / check_point * i;
		check_x = (int)((new_x + cos(angle) * map->player.radius) / BLOCK);
		check_y = (int)((new_y + sin(angle) * map->player.radius) / BLOCK);
		if (check_y < 0 || check_y >= map->height || check_x < 0
			|| check_x >= map->width)
			return (true);
		if (map->map_data[check_y][check_x] == '1')
			return (true);
		i++;
	}
	return (false);
}

void	update_pos(t_coords *player, int speed, t_map *map)
{
	float	new_x;
	float	new_y;

	new_x = player->x;
	new_y = player->y;
	calculate_new_xy(player, speed, &new_x, &new_y);
	if (!is_wall_with_radius(new_x, new_y, map))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_player(t_coords *player, t_game *game)
{
	int		speed;
	float	angle_speed;

	speed = BLOCK / 8;
	angle_speed = 0.1;
	if (player->l_rotate || player->r_rotate)
		player_angle_update(player, angle_speed);
	if (player->up || player->down || player->right || player->left)
		update_pos(player, speed, &game->data->map);
}
