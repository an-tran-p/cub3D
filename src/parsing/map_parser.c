#include "cub3d.h"

int	is_map(char *line)
{
	int	i;
	int	map_chars;

	map_chars = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'S' ||
			line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
			map_chars = 1;
		else if (line[i] != ' ')
		{
			print_error("Invalid map characters\n");
			return (2);
		}
		i++;
	}
	return (map_chars);
}

int	get_line_length(char *line)
{
	int	last_index;

	last_index = ft_strlen(line) - 1;
	while (last_index >= 0 && line[last_index] == ' ')
		last_index--;
	return (last_index + 1);
}

int	validate_player(char *line, t_data *data)
{
	int		i;
	int		player_count;
	char	direction;

	i = 0;
	player_count = 0;
	while (line[i])
	{
		if (line[i] == 'S' || line[i] == 'N' ||
			line[i] == 'E' || line[i] == 'W')
		{
			direction = line[i];
			player_count++;
		}
		i++;
	}
	if (player_count > 1)
		return (print_error(MSG_TOO_MANY_PLAYERS), 1);
	if (player_count == 1)
	{
		if (data->map.direction != 0)
			return (print_error(MSG_TOO_MANY_PLAYERS), 1);
		else
		{
			data->map.direction = direction;
			return (0);
		}
	}
	return (0);
}
float	add_angle(t_data *data)
{
	char dir;

	dir = data->map.direction;
	if (dir == 'N')
		return(3 * M_PI / 2);
	else if (dir == 'S')
		return (M_PI / 2);
	else if (dir == 'W')
		return(M_PI);
	else
		return (0);
}

int	parse_map(t_list *map_start_node, t_data *data)
{
	t_list	*curr;
	int max_width;
	int num_lines;
	char *line;
	int has_empty_line;
	int res_map;
	int line_len;

	curr = map_start_node;
	has_empty_line = 0;
	max_width = 0;
	num_lines = 0;
	while (curr)
	{
		line = (char *)curr->content;
		res_map = is_map(line);
		if (!res_map)
			has_empty_line++;
		else if (res_map == 2)
			return (1);
		else if (res_map == 1)
		{
			if (has_empty_line)
				return (print_error(MSG_EMPTY_LINES), 1);
			if (validate_player(line, data) != 0)
				return (1);
		}
		num_lines++;
		line_len = get_line_length(line);
		if (max_width < line_len)
			max_width = line_len;
		curr = curr->next;
	}
	if (data->map.direction == 0)
		return (print_error(MSG_NO_PLAYER), 1);
	data->map.height = num_lines - has_empty_line;
	data->map.width = max_width;
	data->map.player.angle = add_angle(data);
	if (build_map_grid(map_start_node, data) != 0)
		return (1);
	if (validate_walls(data) != 0)
		return (1);
	if (validate_map_connectivity(data) != 0)
		return (1);
	return (0);
}
