#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_game	game;
	int		fd;

	fd = validate_arg(argc, argv);
	if (parse_scene(fd, &data) != 0)
	{
		free_data(&data);
		return (1);
	}
	game.data = &data;
	// init_player(game->data->map->player); "make function to calculate initial angle from char"
	data.map.player.angle = 3 * M_PI / 2;
	data.map.player.x *= BLOCK;
	data.map.player.y *= BLOCK;
	init_game(&game, &data.map.player);
	mlx_terminate(game.mlx);
	free_data(&data);
	return (0);
}

/* int	main(void)
{
	t_game	*game;

		game = malloc(sizeof(t_game));
		game->data = malloc(sizeof(t_data));
		game->data->map = malloc(sizeof(t_map));
		game->data->map->player = malloc(sizeof(t_coords));
		game->data->map->map_data = init_map();
	init_player(game->data->map->player);
	init_game(game, game->data->map->player);
	init_player(game->data->map->player);
	mlx_terminate(game->mlx);
	return (0);
} */
