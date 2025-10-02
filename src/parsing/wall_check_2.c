/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:44:37 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 10:01:22 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_content_left(char **map, int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (map[row][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	has_content_right(char **map, int row, int col)
{
	int	i;

	i = col + 1;
	while (map[row][i])
	{
		if (map[row][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	has_content_top(char **map, int row, int col)
{
	int	i;

	i = 0;
	while (i < row)
	{
		if (map[i][col] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	has_content_bottom(char **map, int row, int col)
{
	int	i;

	i = row + 1;
	while (map[i])
	{
		if (map[i][col] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_internal_space(char **map, int row, int col)
{
	if (!has_content_left(map, row, col))
		return (0);
	if (!has_content_right(map, row, col))
		return (0);
	if (!has_content_top(map, row, col))
		return (0);
	if (!has_content_bottom(map, row, col))
		return (0);
	return (1);
}
