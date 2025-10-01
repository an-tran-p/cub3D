#include "cub3d.h"

// int	check_diagonal_cells(char **map, int row, int col)
// {
// 	int	coord[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
// 	int	i;
// 	int	new_row;
// 	int	new_col;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		new_row = row + coord[i][0];
// 		new_col = col + coord[i][1];
// 		if (map[new_row][new_col] == ' ')
// 		{
// 			if (is_internal_space(map, new_row, new_col))
// 				return (print_error(MSG_EMPTY_SPACES), 1);
// 			return (print_error(MSG_NO_WALL), 1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }


// int	check_adjacent_cells(char **map, int row, int col, t_data *data)
// {
// 	int	coord[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
// 	int	i;
// 	int	new_row;
// 	int	new_col;
// 	int	width;
// 	int	height;

// 	i = 0;
// 	width = data->map.width;
// 	height = data->map.height;
// 	while (i < 4)
// 	{
// 		new_row = row + coord[i][0];
// 		new_col = col + coord[i][1];
// 		if (new_col < 0 || new_row < 0 || new_col == width || new_row == height)
// 			return (print_error(MSG_NO_WALL), 1);
// 		if (map[new_row][new_col] == ' ')
// 		{
// 			if (is_internal_space(map, new_row, new_col))
// 				return (print_error(MSG_EMPTY_SPACES), 1);
// 			return (print_error(MSG_NO_WALL), 1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

static int	check_single_cell(t_data *data, int row, int col, int off_r, int off_c)
{
    int	new_row;
    int	new_col;
    char    **map;

    map = data->map.map_data;
    new_row = row + off_r;
    new_col = col + off_c;
    if (data && (new_col < 0 || new_row < 0 || 
        new_col >= data->map.width || new_row >= data->map.height))
        return (print_error(MSG_NO_WALL), 1);
    if (map[new_row][new_col] == ' ')
    {
        if (is_internal_space(map, new_row, new_col))
            return (print_error(MSG_EMPTY_SPACES), 1);
        return (print_error(MSG_NO_WALL), 1);
    }
    return (0);
}

int	check_adjacent_cells(t_data *data, int row, int col)
{
    if (check_single_cell(data, row, col, 1, 0) != 0)
        return (1);
    if (check_single_cell(data, row, col, -1, 0) != 0)
        return (1);
    if (check_single_cell(data, row, col, 0, 1) != 0)
        return (1);
    if (check_single_cell(data, row, col, 0, -1) != 0)
        return (1);
    return (0);
}

int	check_diagonal_cells(t_data *data, int row, int col)
{
    if (check_single_cell(data, row, col, 1, 1) != 0)
        return (1);
    if (check_single_cell(data, row, col, 1, -1) != 0)
        return (1);
    if (check_single_cell(data, row, col, -1, 1) != 0)
        return (1);
    if (check_single_cell(data, row, col, -1, -1) != 0)
        return (1);
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
			if (map[i][j] == '0' || map[i][j] == 'S' || map[i][j] == 'N'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (check_adjacent_cells(data, i, j) != 0
					|| check_diagonal_cells(data, i, j) != 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
