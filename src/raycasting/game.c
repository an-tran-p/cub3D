#include "cub3d.h"

void	init_game(t_game *game, t_coords *player)
{
	player->radius = BLOCK / 3;
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
	mlx_key_hook(game->mlx, handle_keyhook, player);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
