#include "cub3d.h"

int	check_texture_access(char *path)
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

int check_texture_ext(char *path)
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

int count_path_len(char *line)
{
    size_t  len;

    len = 0;
    while (line[len] && line[len] != '\n')
        len++;
    return (len);
}

int    save_texture(char **path, char *line)
{
    int     i;
    size_t     len;

    i = 0;
    while (line[i] == ' ')
        i++;
    if (line[i] == '\0' || line[i] == '\n')
        return (print_error("Missing texture path\n"), 1);
    if (*path)
        return (print_error("Similar texture identifies\n"), 1);
    len = count_path_len(line + i);
    *path = ft_strndup(line + i, len);
    printf("%s ", *path);
    if (!(*path))
        return (print_error("Malloc failed\n"), 1);
    if (check_texture_ext(*path) != 0 || check_texture_access(*path))
        return (1);
    return (0);
}
