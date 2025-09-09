#include "cub3d.h"

void    check_file_access(char *file_name)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        if (errno == ENOENT)
            print_error(MSG_NO_FILE);
        else if (errno == EACCES)
            print_error(MSG_PERM_DENIED);
        else if (errno == EISDIR)
            print_error(MSG_IS_DIR);
        else
            print_error(strerror(errno));
        exit (1);
    }
    close(fd);
}

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
    check_file_access(argv[1]);
}