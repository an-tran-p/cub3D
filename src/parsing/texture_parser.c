#include "cub3d.h"

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
    if (*path)
    {
        print_error("Similar texture identifies\n");
        return (1);
    }
    len = count_path_len(line + i);
    *path = ft_strndup(line + i, len);
    printf("%s ", *path);
    if (!(*path))
    {
        print_error("Malloc failed\n");
        return (1);
    }
    return (0);
}
