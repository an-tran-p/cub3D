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

void	up_down_pos_update(t_coords *player, int speed, char **map)
{
	float	new_x;
	float	new_y;

	if (player->up)
	{
		new_x = player->x + cos(player->angle) * speed;
		new_y = player->y + sin(player->angle) * speed;
		if (map[(int)(new_y / BLOCK)][(int)(new_x / BLOCK)] == '0')
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->down)
	{
		new_x = player->x - cos(player->angle) * speed;
		new_y = player->y - sin(player->angle) * speed;
		if (map[(int)(new_y / BLOCK)][(int)(new_x / BLOCK)] == '0')
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}

void	left_right_pos_update(t_coords *player, int speed, char **map)
{
	float	new_x;
	float	new_y;

	if (player->left)
	{
		new_x = player->x + sin(player->angle) * speed;
		new_y = player->y - cos(player->angle) * speed;
		if (map[(int)(new_y / BLOCK)][(int)(new_x / BLOCK)] == '0')
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (player->right)
	{
		new_x = player->x - sin(player->angle) * speed;
		new_y = player->y + cos(player->angle) * speed;
		if (map[(int)(new_y / BLOCK)][(int)(new_x / BLOCK)] == '0')
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
}

void	move_player(t_coords *player, t_game *game)
{
	int		speed;
	float	angle_speed;

	speed = 1;
	angle_speed = 0.1;
	player_angle_update(player, angle_speed);
	up_down_pos_update(player, speed, game->data->map.map_data);
	left_right_pos_update(player, speed, game->data->map.map_data);
}
