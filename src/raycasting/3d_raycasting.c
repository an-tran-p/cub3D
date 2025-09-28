#include "cub3d.h"

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float ray_x, float ray_y, t_coords *player)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = ray_x - player->x;
	delta_y = ray_y - player->y;
	angle = atan2(delta_y, delta_x) - player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	if (fix_dist < 0.1f)
		fix_dist = 0.1f;
	return (fix_dist);
}

void	view_3d(t_coords *player, t_game *game, float start_x, int i)
{
	float	height;
	int		start_y;
	int		end;
	float	ray_x;
	float	ray_y;
    int     y;

	ray_x = player->x + cos(start_x) * player->radius;
	ray_y = player->y + sin(start_x) * player->radius;
	while (!touch(ray_x, ray_y, game->data->map))
	{
		ray_x += cos(start_x) * 0.5f;
		ray_y += sin(start_x) * 0.5f;
	}
	height = (BLOCK * (WIDTH / 2) / tan((M_PI / 3) / 2)) / fixed_dist(ray_x,
			ray_y, player);
	start_y = (HEIGHT - height) / 2;
	end = start_y + height;
	if (start_y < 0)
		start_y = 0;
    //Draw ceiling (top to wall start)
    y = 0;
    while (y < start_y)
    {
        mlx_put_pixel(game->image, i, y, game->data->c_color);
        y++;
    }
	while (start_y < end && start_y < HEIGHT)
	{
		mlx_put_pixel(game->image, i, start_y, 0x0000FFFF);
		start_y++;
	}
    //Draw floor (wall end to bottom)
    y = end;
    while (y < HEIGHT)
    {
        mlx_put_pixel(game->image, i, y, game->data->f_color);
        y++;
    }
}

void	casting_ray(t_game *game)
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
