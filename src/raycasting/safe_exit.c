#include "cub3d.h"

void	free_game_imgs(t_game *game)
{
	if (game->no_wall)
		mlx_delete_image(game->mlx, game->no_wall);
	if (game->so_wall)
		mlx_delete_image(game->mlx, game->so_wall);
	if (game->we_wall)
		mlx_delete_image(game->mlx, game->we_wall);
	if (game->ea_wall)
		mlx_delete_image(game->mlx, game->ea_wall);
	if (game->image)
		mlx_delete_image(game->mlx, game->image);
	if (game->mini_map)
		mlx_delete_image(game->mlx, game->mini_map);
}

void	error_exit_game(char *msg, t_game *game)
{
	if (msg)
		print_error(msg);
	free_data(game->data);
	free_game_imgs(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(1);
}