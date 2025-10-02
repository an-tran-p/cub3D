/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:44:16 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 09:44:18 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_texture_access(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error(MSG_NO_ACCESS_TO_TEXTURE);
		return (1);
	}
	close(fd);
	return (0);
}

int	validate_texture_ext(char *path)
{
	char	*ptr;

	ptr = ft_strrchr(path, '.');
	if (!ptr || (ft_strcmp(ptr, ".png") != 0))
	{
		print_error(MSG_WRONG_TEXTURE_EXT);
		return (1);
	}
	return (0);
}

int	count_path_len(char *line)
{
	size_t	len;

	len = 0;
	while (line[len] && line[len] != ' ')
		len++;
	return (len);
}

int	save_texture_path(char **texture_path, char *path_start, t_data *data)
{
	int		i;
	size_t	len;

	i = 0;
	while (path_start[i] == ' ')
		i++;
	len = count_path_len(path_start + i);
	if (data->no_path && len == ft_strlen(data->no_path)
		&& !ft_strncmp(path_start + i, data->no_path, len))
		return (print_error(MSG_DUP_TEXTURE), 1);
	if (data->so_path && len == ft_strlen(data->so_path)
		&& !ft_strncmp(path_start + i, data->so_path, len))
		return (print_error(MSG_DUP_TEXTURE), 1);
	if (data->we_path && len == ft_strlen(data->we_path)
		&& !ft_strncmp(path_start + i, data->we_path, len))
		return (print_error(MSG_DUP_TEXTURE), 1);
	if (data->ea_path && len == ft_strlen(data->ea_path)
		&& !ft_strncmp(path_start + i, data->ea_path, len))
		return (print_error(MSG_DUP_TEXTURE), 1);
	*texture_path = ft_strndup(path_start + i, len);
	if (!(*texture_path))
		return (print_error("Malloc failed\n"), 1);
	return (0);
}

int	save_texture(char **texture_path, char *line, int id_pos, t_data *data)
{
	char	*path_start;

	if (validate_texture_line(line, id_pos) != 0)
		return (1);
	if (*texture_path)
		return (print_error("Duplicate texture identifier\n"), 1);
	path_start = line + id_pos + 3;
	if (save_texture_path(texture_path, path_start, data) != 0)
		return (1);
	if (validate_texture_ext(*texture_path) != 0
		|| validate_texture_access(*texture_path) != 0)
		return (1);
	return (0);
}
