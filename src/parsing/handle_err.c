#include "cub3d.h"

void    print_error(char *err_msg)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
    ft_putstr_fd(err_msg, STDERR_FILENO);
}