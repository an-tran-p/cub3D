#include "cub3d.h"

int    save_texture(char **path, char *line)
{
    int     i;

    i = 0;
    while (line[i] == ' ')
        i++;
    if (*path)
    {
        print_error("Similar texture identifies\n");
        return (1);
    }
    *path = ft_strdup(line + i);
    if (!(*path))
    {
        print_error("Malloc failed\n");
        return (1);
    }
    return (0);
}
