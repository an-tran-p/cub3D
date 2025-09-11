#include "cub3d.h"

void    print_error(char *err_msg)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
    ft_putstr_fd(err_msg, STDERR_FILENO);
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