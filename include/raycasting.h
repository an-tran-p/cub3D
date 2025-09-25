#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 1920
# define HEIGHT 1080

# define BLOCK 30

# define CUB2D 0

typedef struct s_game
{
	void	*mlx;
	void	*image;
	t_data	*data;
}			t_game;

void		draw_block(int x, int y, int size, uint32_t color, t_game *game);
void		draw_map(t_game *game, char **map);
void		handle_keyhook(mlx_key_data_t keydata, void *param);
void		move_player(t_coords *player, t_game *game);
void		game_loop(void *param);
void		casting_ray(t_game *game);
void		init_game(t_game *game, t_coords *player);

#endif
