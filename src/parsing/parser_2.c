#include "cub3d.h"


int	check_identifier(char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] != 'O')
		return (print_error("Unknown identifier starts with N\n"), 1);
	else if (line[i] == 'S' && line[i + 1] != 'O')
		return (print_error("Unknown identifier starts with S\n"), 1);
	else if (line[i] == 'W' && line[i + 1] != 'E')
		return (print_error("Unknown identifier starts with W\n"), 1);
	else if (line[i] == 'E' && line[i + 1] != 'A')
		return (print_error("Unknown identifier starts with E\n"), 1);
	if (line[i + 2] == '\0')
		return (print_error("Missing texture path\n"), 1);
	if (line[i] == 'N' && line[i + 2] != ' ')
		return (print_error("No space after NO identifier\n"), 1);
	else if (line[i] == 'S' && line[i + 2] != ' ')
		return (print_error("No space after SO identifier\n"), 1);
	else if (line[i] == 'W' && line[i + 2] != ' ')
		return (print_error("No space after WE identifier\n"), 1);
	else if (line[i] == 'E' && line[i + 2] != ' ')
		return (print_error("No space after EA identifier\n"), 1);
	return (0);
}

int	validate_texture_line(char *line, int id_pos)
{
	char	*path_start;
	int		i;

	if (check_identifier(line, id_pos) != 0)
		return (1);
	path_start = line + id_pos + 3;
	i = 0;
	while (path_start[i] && path_start[i] == ' ')
		i++;
	if (path_start[i] == '\0')
		return (print_error("Missing texture path\n"), 1);
	while (path_start[i])
	{
		if (path_start[i] == ' ')
		{
			while (path_start[i] && path_start[i] == ' ')
				i++;
			if (path_start[i] != '\0')
				return (print_error("Invalid extra characters in a texture line\n"),
					1);
		}
		i++;
	}
	return (0);
}

int	check_required_elements(t_data *data)
{
	int	has_error;

	has_error = 0;
	if (!data->no_path && print_error(MSG_MISSING_NO))
		has_error = 1;
	if (!data->so_path && print_error(MSG_MISSING_SO))
		has_error = 1;
	if (!data->ea_path && print_error(MSG_MISSING_EA))
		has_error = 1;
	if (!data->we_path && print_error(MSG_MISSING_WE))
		has_error = 1;
	if (data->f_color == (uint32_t)-1 && print_error(MSG_MISSING_F))
		has_error = 1;
	if (data->c_color == (uint32_t)-1 && print_error(MSG_MISSING_C))
		has_error = 1;
	return (has_error);
}

int	parse_map(t_list *map_start_node, t_data *data)
{
	if (scan_map_structure(map_start_node, data) != 0)
		return (1);
	if (data->map.direction == 0)
		return (print_error(MSG_NO_PLAYER), 1);
	if (build_map_grid(map_start_node, data) != 0)
		return (1);
	if (validate_walls(data) != 0)
		return (1);
	if (validate_map_connectivity(data) != 0)
		return (1);
	return (0);
}