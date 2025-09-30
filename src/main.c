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
	data.map.player.x *= BLOCK;
	data.map.player.y *= BLOCK;
	init_game(&game, &data.map.player);
	mlx_terminate(game.mlx);
	free_data(&data);
	return (0);
}
