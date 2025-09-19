#include "cub3d.h"

int	check_file_access(char *path_to_file)
{
	int	fd;

	if (!path_to_file)
		return (1);
	fd = open(path_to_file, O_RDONLY);
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
		exit(1);
	}
	return (fd);
}

void	check_ext(char *path_to_file)
{
	char	*ptr;

	ptr = ft_strrchr(path_to_file, '.');
	if (!ptr || (ft_strcmp(ptr, ".cub") != 0))
	{
		print_error(MSG_WRONG_FILE_EXT);
		exit(1);
	}
}

int	validate_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error(MSG_NO_ARG);
		exit(1);
	}
	if (argv[1][0] == '\0')
	{
		print_error(MSG_EMPTY_ARG);
		exit(1);
	}
	check_ext(argv[1]);
	return (check_file_access(argv[1]));
}
