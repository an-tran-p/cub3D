/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:45:22 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 10:37:12 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_single_cell(t_data *data, t_cell pos, t_cell offset)
{
	int		new_row;
	int		new_col;
	char	**map;

	map = data->map.map_data;
	new_row = pos.row + offset.row;
	new_col = pos.col + offset.col;
	if (new_col < 0 || new_row < 0 || new_col >= data->map.width
		|| new_row >= data->map.height)
		return (print_error(MSG_NO_WALL), 1);
	if (map[new_row][new_col] == ' ')
	{
		if (is_internal_space(map, new_row, new_col))
			return (print_error(MSG_EMPTY_SPACES), 1);
		return (print_error(MSG_NO_WALL), 1);
	}
	return (0);
}

int	check_adjacent_cells(t_data *data, t_cell pos)
{
	if (check_single_cell(data, pos, (t_cell){1, 0}) != 0)
		return (1);
	if (check_single_cell(data, pos, (t_cell){-1, 0}) != 0)
		return (1);
	if (check_single_cell(data, pos, (t_cell){0, 1}) != 0)
		return (1);
	if (check_single_cell(data, pos, (t_cell){0, -1}) != 0)
		return (1);
	return (0);
}

int	check_diagonal_cells(t_data *data, t_cell pos)
{
	if (check_single_cell(data, pos, (t_cell){1, 1}) != 0)
		return (1);
	if (check_single_cell(data, pos, (t_cell){1, -1}) != 0)
		return (1);
	if (check_single_cell(data, pos, (t_cell){-1, 1}) != 0)
		return (1);
	if (check_single_cell(data, pos, (t_cell){-1, -1}) != 0)
		return (1);
	return (0);
}

int	validate_walls(t_data *data)
{
	char	**map;
	t_cell	pos;

	pos.row = 0;
	map = data->map.map_data;
	while (map[pos.row])
	{
		pos.col = 0;
		while (map[pos.row][pos.col])
		{
			if (map[pos.row][pos.col] == '0' || map[pos.row][pos.col] == 'S'
				|| map[pos.row][pos.col] == 'N' || map[pos.row][pos.col] == 'E'
				|| map[pos.row][pos.col] == 'W')
			{
				if (check_adjacent_cells(data, pos) != 0
					|| check_diagonal_cells(data, pos) != 0)
					return (1);
			}
			pos.col++;
		}
		pos.row++;
	}
	return (0);
}
