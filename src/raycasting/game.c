#include "cub3d.h"

// void	view_3d(t_coords *player, t_game *game, float start_x, int i)
// {
// 	float	dist;
// 	float	height;
// 	int		start_y;
// 	int		end;
// 	float	ray_x;
// 	float	ray_y;
//     int     y;

// 	ray_x = player->x;
// 	ray_y = player->y;
// 	while (!touch(ray_x, ray_y, game->data->map))
// 	{
// 		ray_x += cos(start_x);
// 		ray_y += sin(start_x);
// 	}
// 	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
// 	height = (BLOCK / dist) * (WIDTH / 2);
// 	start_y = (HEIGHT - height) / 2;
// 	end = start_y + height;
//     //Draw ceiling (top to wall start)
//     y = 0;
//     while (y < start_y)
//     {
//         mlx_put_pixel(game->image, i, y, game->data->c_color);
//         y++;
//     }
// 	while (start_y < end)
// 	{
// 		mlx_put_pixel(game->image, i, start_y, 0x0000FFFF);
// 		start_y++;
// 	}
//     //Draw floor (wall end to bottom)
//     y = end;
//     while (y < HEIGHT)
//     {
//         mlx_put_pixel(game->image, i, y, game->data->f_color);
//         y++;
//     }
// }

void	init_game(t_game *game, t_coords *player)
{
	player->radius = BLOCK / 10;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		return ;
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return ;
	if (CUB2D)
	{
		draw_block(player->x, player->y, 1, 0xFF0000FF, game);
		draw_map(game, game->data->map.map_data);
	}
	load_and_resize_textures(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
	mlx_key_hook(game->mlx, handle_keyhook, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
