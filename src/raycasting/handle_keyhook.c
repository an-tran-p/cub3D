#include "cub3d.h"

void	key_press(mlx_key_data_t keydata, t_coords *player)
{
	if (keydata.key == MLX_KEY_W)
		player->up = true;
	if (keydata.key == MLX_KEY_S)
		player->down = true;
	if (keydata.key == MLX_KEY_A)
		player->left = true;
	if (keydata.key == MLX_KEY_D)
		player->right = true;
	if (keydata.key == MLX_KEY_LEFT)
		player->l_rotate = true;
	if (keydata.key == MLX_KEY_RIGHT)
		player->r_rotate = true;
}

void	key_release(mlx_key_data_t keydata, t_coords *player)
{
	if (keydata.key == MLX_KEY_W)
		player->up = false;
	if (keydata.key == MLX_KEY_S)
		player->down = false;
	if (keydata.key == MLX_KEY_A)
		player->left = false;
	if (keydata.key == MLX_KEY_D)
		player->right = false;
	if (keydata.key == MLX_KEY_LEFT)
		player->l_rotate = false;
	if (keydata.key == MLX_KEY_RIGHT)
		player->r_rotate = false;
}

void	handle_keyhook(mlx_key_data_t keydata, void *param)
{
	t_coords	*player;

	player = (t_coords *)param;
	if (keydata.action == MLX_PRESS)
		key_press(keydata, player);
	else if (keydata.action == MLX_RELEASE)
		key_release(keydata, player);
}

void	game_loop(void *param)
{
	t_game		*game;
	t_coords	*player;

	game = (t_game *)param;
	player = &game->data->map.player;
	move_player(player, game);
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
		return ;
	if (CUB2D)
	{
		draw_block(player->x, player->y, BLOCK, 0xFF0000FF, game);
		draw_map(game, game->data->map.map_data);
	}
	casting_ray(game);
	mlx_image_to_window(game->mlx, game->image, 0, 0);
}
