#include "cub3d.h"

int	main(int argc, char **argv)
{
	char *map[] = {
		"1111111111",
		"1000000001",
		"1010110001",
		"1000011101",
		"100000N001",
		"1111111111",
		NULL
	};
	t_data	data;
	int fd;
	t_list	*head;

	data.map.map_data = map;
	fd = validate_arg(argc, argv);
	head = parse_scene(fd);

	ft_lstclear(&head, free);
	close(fd);
	return (0);
}