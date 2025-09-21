#include "cub3d.h"

int    print_error(char *err_msg)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
    ft_putstr_fd(err_msg, STDERR_FILENO);
    return (1);
}

void    free_data(t_data *data)
{
    int rows;

    rows = data->map.height;
    free(data->no_path);
    free(data->so_path);
    free(data->we_path);
    free(data->ea_path);
    if (data->map.map_data)
    {
        while (--rows >= 0)
            free(data->map.map_data[rows]);
        free(data->map.map_data);
    }
}

int has_map_chars(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '1' || line[i] == '0' || line[i] == 'S' || 
            line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
            return (1);
        i++;
    }
    return (0);
}