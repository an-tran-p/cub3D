/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:43:23 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 09:56:58 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
