#include "cub3d.h"

void	check_ext(char *file_name)
{
	char *ptr;

	ptr = ft_strrchr(file_name, '.');
	if (!ptr || (ft_strcmp(ptr, ".cub") != 0))
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("A scene file should have .cub extension\n", 2);
		exit (1);
	}
	if (ft_strlen(file_name) == 4)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Specify file name before .cub extension\n", 2);
		exit (1);
	}
}

void	validate_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Include one scene file as argument\n", 2);
		exit (1);
	}
	if (argv[1][0] == '\0')
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Specify a scene file with .cub extension\n", 2);
		exit (1);
	}
	check_ext(argv[1]);
}