#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>

typedef struct s_coords
{
	int			x;
	int			y;
}				t_coords;

typedef struct s_map
{
	char		**map_data;
	int			width;
	int			height;
	t_coords	player;
	char		direction;
	int			max_width;
	bool		is_valid;
}				t_map;

typedef struct s_data
{
	uint32_t	f_color;
	uint32_t	c_color;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_map		map;
}				t_data;

int				validate_arg(int argc, char **argv);
void			print_error(char *err_msg);
int			    parse_scene(int fd, t_data *data);
void            free_data(t_data *data);
int             save_texture(char **path, char *line);
int             save_color(uint32_t	*color, char *line);

#endif