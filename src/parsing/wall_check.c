#include "cub3d.h"

int	is_internal_space(char *line, int col)
{
	int	i;
	int	cont_before;
	int	cont_after;

	i = 0;
	cont_before = 0;
	cont_after = 0;
	while (i < col)
	{
		if (line[i] != ' ')
			cont_before = 1;
		i++;
	}
	i = col;
	while (line[i])
	{
		if (line[i] != ' ')
			cont_after = 1;
		i++;
	}
	if (cont_before && cont_after)
		return (1);
	return (0);
}

int	check_diagonal_cells(char **map, int row, int col)
{
	int	coord[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	int	i;
	int	new_row;
	int	new_col;

	i = 0;
	while (i < 4)
	{
		new_row = row + coord[i][0];
		new_col = col + coord[i][1];
		if (map[new_row][new_col] == ' ')
		{
			if (is_internal_space(map[new_row], new_col))
				return (print_error(MSG_EMPTY_SPACES), 1);
			return (print_error(MSG_NO_WALL), 1);
		}
		i++;
	}
	return (0);
}

int	check_adjacent_cells(char **map, int row, int col, t_data *data)
{
	int	coord[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int	i;
	int	new_row;
	int	new_col;
	int	width;
	int	height;

	i = 0;
	width = data->map.width;
	height = data->map.height;
	while (i < 4)
	{
		new_row = row + coord[i][0];
		new_col = col + coord[i][1];
		if (new_col < 0 || new_row < 0 || new_col == width || new_row == height)
			return (print_error(MSG_NO_WALL), 1);
		if (map[new_row][new_col] == ' ')
		{
			if (is_internal_space(map[new_row], new_col))
				return (print_error(MSG_EMPTY_SPACES), 1);
			return (print_error(MSG_NO_WALL), 1);
		}
		i++;
	}
	return (0);
}

int	validate_walls(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = data->map.map_data;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (check_adjacent_cells(map, i, j, data) != 0 || check_diagonal_cells(map, i, j) != 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_map_line(char *dst, char *src, int width)
{
	int	j;

	j = 0;
	while (src[j] && j < width)
	{
		dst[j] = src[j];
		j++;
	}
	while (j < width)
	{
		dst[j] = ' ';
		j++;
	}
	dst[width] = '\0';
}

int	build_map_grid(t_list *map_start_node, t_data *data)
{
	int		i;
	char	**map;
	t_list	*curr;
	char	*line;

	map = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!map)
		return (1);
	i = 0;
	curr = map_start_node;
	while (i < data->map.height && curr)
	{
		line = (char *)curr->content;
		map[i] = malloc(sizeof(char) * (data->map.width + 1));
		if (!map[i])
			return (free_map(map, i), 1);
		fill_map_line(map[i], line, data->map.width);
		i++;
		curr = curr->next;
	}
	data->map.map_data = map;
	return (0);
}
