#include "cub3d.h"

void	check_ext(char *file_name)
{
	char *ptr;

	ptr = ft_strrchr(file_name, '.');
	if (!ptr || (ft_strcmp(ptr, ".cub") != 0))
	{
        print_error(MSG_WRONG_EXT);
		exit (1);
	}
}

void	validate_arg(int argc, char **argv)
{
	if (argc != 2)
	{
        print_error(MSG_NO_ARG);
		exit (1);
	}
	if (argv[1][0] == '\0')
	{
        print_error(MSG_EMPTY_ARG);
		exit (1);
	}
	check_ext(argv[1]);
}