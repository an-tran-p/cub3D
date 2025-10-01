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
void	flood_fill_connectivity(char **map, int col, int row, int height,
		int width)
{
	if (col < 0 || row < 0 || col >= width || row >= height)
		return ;
	if (map[row][col] == ' ' || map[row][col] == 'V')
		return ;
	if (map[row][col] == '1' || map[row][col] == '0' || map[row][col] == 'S'
		|| map[row][col] == 'N' || map[row][col] == 'E' || map[row][col] == 'W')
	{
		map[row][col] = 'V';
		flood_fill_connectivity(map, col + 1, row, height, width);
		flood_fill_connectivity(map, col - 1, row, height, width);
		flood_fill_connectivity(map, col, row + 1, height, width);
		flood_fill_connectivity(map, col, row - 1, height, width);
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
				print_error("Map contant outside the enclosed area\n");
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
	int		height;
	int		width;

	find_player_coords(data);
	map_copy = build_map_copy(data->map.height, data);
	if (!map_copy)
		return (1);
	col = data->map.player.x;
	row = data->map.player.y;
	width = data->map.width;
	height = data->map.height;
	flood_fill_connectivity(map_copy, col, row, height, width);
	if (validate_visited(map_copy) != 0)
	{
		free_map(map_copy, height);
		return (1);
	}
	free_map(map_copy, height);
	return (0);
}
