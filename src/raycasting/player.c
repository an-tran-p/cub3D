#include "cub3d.h"

void	player_angle_update(t_coords *player, float angle_speed)
{
	if (player->l_rotate)
	{
		player->angle -= angle_speed;
		// player->l_rotate = false;
	}
	if (player->r_rotate)
	{
		player->angle += angle_speed;
		// player->r_rotate = false;
	}
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
		printf("old x: %f, y: %f\n", player->x, player->y);
		*new_x = player->x + cos(player->angle) * speed;
		*new_y = player->y + sin(player->angle) * speed;
		printf("new x: %f, y: %f\n", *new_x, *new_y);
	}
	if (player->down)
	{
		printf("old x: %f, y: %f\n", player->x, player->y);
		*new_x = player->x - cos(player->angle) * speed;
		*new_y = player->y - sin(player->angle) * speed;
		printf("new x: %f, y: %f\n", *new_x, *new_y);
	}
	if (player->left)
	{
		printf("old x: %f, y: %f\n", player->x, player->y);
		*new_x = player->x + sin(player->angle) * speed;
		*new_y = player->y - cos(player->angle) * speed;
		printf("new x: %f, y: %f\n", *new_x, *new_y);
	}
	if (player->right)
	{
		printf("old x: %f, y: %f\n", player->x, player->y);
		*new_x = player->x - sin(player->angle) * speed;
		*new_y = player->y + cos(player->angle) * speed;
		printf("new x: %f, y: %f\n", *new_x, *new_y);
	}
}

bool	is_wall(float new_x, float new_y, t_map *map)
{
	int	map_x;
	int	map_y;

	map_x = (int)(new_x / BLOCK);
	map_y = (int)(new_y / BLOCK);
	printf("BEFORE IF: the new coor is %c\n", map->map_data[map_y][map_x]);
	printf("map height is %d, map width is %d\n", map->height, map->width);
	if (map_y >= 0 && map_y < map->height && map_x >= 0 && map_x < map->width
		&& map->map_data[map_y][map_x] == '0')
	{
		printf("the new coor is %c\n", map->map_data[map_y][map_x]);
		return (false);
	}
	return (true);
}

void	update_pos(t_coords *player, int speed, t_map *map)
{
	float	new_x;
	float	new_y;

	calculate_new_xy(player, speed, &new_x, &new_y);
	if (!is_wall(new_x, new_y, map))
	{
		map->player.x = new_x;
		map->player.y = new_y;
	}
}

void	move_player(t_coords *player, t_game *game)
{
	int		speed;
	float	angle_speed;

	speed = BLOCK / 16;
	angle_speed = 0.5;
	player_angle_update(player, angle_speed);
	update_pos(player, speed, &game->data->map);
}
