/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:42:48 by atran             #+#    #+#             */
/*   Updated: 2025/10/02 10:47:20 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(float px, float py, t_map map)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (y < 0 || y >= map.height || x < 0 || x >= map.width)
		return (true);
	if (map.map_data[y][x] == '1')
		return (true);
	return (false);
}

uint32_t	get_image_pixel(mlx_image_t *img, int x, int y)
{
	uint8_t	*px;

	px = &img->pixels[(y * img->width + x) * 4];
	return (px[0] << 24 | px[1] << 16 | px[2] << 8 | px[3]);
}
