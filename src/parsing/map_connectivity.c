/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_connectivity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:43:44 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 10:08:25 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player_coords(t_data *data)
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
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				data->map.player.x = j + 0.5;
				data->map.player.y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

char	**build_map_copy(int height, t_data *data)
{
	char	**map_copy;
	char	**map;
	int		i;

	i = 0;
	map = data->map.map_data;
	map_copy = ft_calloc(height + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy, i);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

void	flood_fill_connectivity(char **map, int col, int row, t_data *data)
{
	if (col < 0 || row < 0 || col >= data->map.width || row >= data->map.height)
		return ;
	if (map[row][col] == ' ' || map[row][col] == 'V')
		return ;
	if (map[row][col] == '1' || map[row][col] == '0' || map[row][col] == 'S'
		|| map[row][col] == 'N' || map[row][col] == 'E' || map[row][col] == 'W')
	{
		map[row][col] = 'V';
		flood_fill_connectivity(map, col + 1, row, data);
		flood_fill_connectivity(map, col - 1, row, data);
		flood_fill_connectivity(map, col, row + 1, data);
		flood_fill_connectivity(map, col, row - 1, data);
	}
}

int	validate_visited(char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == '1' || map_copy[i][j] == '0')
			{
				print_error("Map contains unreachable areas\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map_connectivity(t_data *data)
{
	char	**map_copy;
	int		col;
	int		row;

	find_player_coords(data);
	map_copy = build_map_copy(data->map.height, data);
	if (!map_copy)
		return (1);
	col = data->map.player.x;
	row = data->map.player.y;
	flood_fill_connectivity(map_copy, col, row, data);
	if (validate_visited(map_copy) != 0)
	{
		free_map(map_copy, data->map.height);
		return (1);
	}
	free_map(map_copy, data->map.height);
	return (0);
}
