#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>

typedef struct s_coords
{
	float		x;
	float		y;
	float		radius;
	float		angle;
	bool		up;
	bool		down;
	bool		left;
	bool		right;
	bool		l_rotate;
	bool		r_rotate;
}				t_coords;

typedef struct s_map
{
	char		**map_data;
	int			width;
	int			height;
	t_coords	player;
	char		direction;
}				t_map;

typedef struct s_data
{
	uint32_t	f_color;
	uint32_t	c_color;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_list		*map_start_node;
	t_map		map;
}				t_data;

int				validate_arg(int argc, char **argv);
int				print_error(char *err_msg);
int				parse_scene(int fd, t_data *data);
void			free_data(t_data *data);
int				save_color(uint32_t *color, char *line);
int				save_texture(char **texture_path, char *line, int id_pos,
					t_data *data);
int				is_map(char *line);
int				has_map_chars(char *line);
int				parse_map(t_list *map_start_node, t_data *data);
int				build_map_grid(t_list *map_start_node, t_data *data);
int				validate_walls(t_data *data);
int				validate_map_connectivity(t_data *data);
void			free_map(char **map_copy, int i);

#endif
