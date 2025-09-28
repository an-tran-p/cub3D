#include "cub3d.h"

void	load_and_resize_img(t_game *game, char *src_path, mlx_image_t **dst)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(src_path);
	if (!texture)
		error_exit_game("MLX failed to initialize\n", game);
	(*dst) = mlx_texture_to_image(game->mlx, texture);
	if (!(*dst))
	{
		mlx_delete_texture(texture);
		error_exit_game("MLX failed to initialize\n", game);
	}
	mlx_delete_texture(texture);
	if (!mlx_resize_image(*dst, BLOCK, BLOCK))
		error_exit_game("Failed to resize texture\n", game);
}

void	load_and_resize_textures(t_game *game)
{
	load_and_resize_img(game, game->data->no_path, &game->no_wall);
	load_and_resize_img(game, game->data->so_path, &game->so_wall);
	load_and_resize_img(game, game->data->we_path, &game->we_wall);
	load_and_resize_img(game, game->data->ea_path, &game->ea_wall);
}
