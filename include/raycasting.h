#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIDTH 1920
# define HEIGHT 1080

# define BLOCK 128

# define VERTICAL_WALL 0
# define HORIZONTAL_WALL 1

# define MINIMAP_WIDTH	400
# define MINIMAP_HEIGHT	200

typedef enum e_wall_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_wall_side;

typedef struct s_ray
{
	float		angle;
	float		ray_x;
	float		ray_y;
	int			step_x;
	int			step_y;
	float		dist;
	float		height;
	int			start_y;
	int			end;
	int			wall;
	t_wall_side	side;
}				t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*image;
	int			tex_size;
	mlx_image_t	*mini_map;
	int			minimap_scale;
	mlx_image_t	*no_wall;
	mlx_image_t	*so_wall;
	mlx_image_t	*ea_wall;
	mlx_image_t	*we_wall;
	t_data		*data;
}				t_game;

void			init_game(t_game *game, t_coords *player);
void			draw_block(int x, int y, int size, uint32_t color,
					t_game *game);
void			draw_map(t_game *game, char **map);
void			draw_ray_2d(t_coords *player, t_game *game, float start_x);
void			handle_keyhook(mlx_key_data_t keydata, void *param);
void			move_player(t_coords *player, t_game *game);
void			game_loop(void *param);
void			render_frame(t_game *game);
bool			touch(float px, float py, t_map map);

void			load_and_resize_textures(t_game *game);
void			error_exit_game(char *msg, t_game *game);

#endif
