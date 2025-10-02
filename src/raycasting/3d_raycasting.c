/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atran <atran@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:20:08 by atran             #+#    #+#             */
/*   Updated: 2025/10/02 10:54:09 by atran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_wall_x(float *wall_x, t_ray *ray)
{
	if (ray->side == NORTH || ray->side == SOUTH)
		*wall_x = fmod(ray->ray_x, BLOCK) / (float)BLOCK;
	else
		*wall_x = fmod(ray->ray_y, BLOCK) / (float)BLOCK;
}

void	put_wall_texture(t_ray *ray, t_game *game, int y, int i)
{
	int			d;
	float		wall_x;
	int			tex_x;
	int			tex_y;
	uint32_t	pixel_color;

	calculate_wall_x(&wall_x, ray);
	tex_x = (int)(wall_x * (float)game->tex_size);
	d = y - (HEIGHT - ray->height) / 2;
	tex_y = (int)((float)d / ray->height * game->tex_size);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= game->tex_size)
		tex_y = game->tex_size - 1;
	if (ray->side == NORTH)
		pixel_color = get_image_pixel(game->no_wall, tex_x, tex_y);
	else if (ray->side == SOUTH)
		pixel_color = get_image_pixel(game->so_wall, tex_x, tex_y);
	else if (ray->side == EAST)
		pixel_color = get_image_pixel(game->ea_wall, tex_x, tex_y);
	else
		pixel_color = get_image_pixel(game->we_wall, tex_x, tex_y);
	mlx_put_pixel(game->image, i, y, pixel_color);
}

void	view_3d(t_coords *player, t_game *game, float start_x, int i)
{
	t_ray	ray;
	int		y;

	ray = casting_ray(player, game, start_x);
	y = -1;
	while (y++ < ray.start_y)
		mlx_put_pixel(game->image, i, y, game->data->c_color);
	y = ray.start_y;
	while (y < ray.end && y < HEIGHT)
	{
		put_wall_texture(&ray, game, y, i);
		y++;
	}
	y = ray.end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->image, i, y, game->data->f_color);
		y++;
	}
}

void	render_frame(t_game *game)
{
	float		fraction;
	float		start_x;
	t_coords	*player;
	int			i;

	player = &game->data->map.player;
	start_x = player->angle - M_PI / 6;
	i = 0;
	fraction = M_PI / 3 / WIDTH;
	draw_map(game, game->data->map.map_data);
	while (i < WIDTH)
	{
		view_3d(player, game, start_x, i);
		draw_ray_2d(player, game, start_x);
		start_x += fraction;
		i++;
	}
	draw_2d_player(game);
}
