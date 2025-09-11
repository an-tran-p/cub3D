#include "cub3d.h"

int	main(int argc, char **argv)
{
	// char *map[] = {
	// 	"1111111111",
	// 	"1000000001",
	// 	"1010110001",
	// 	"1000011101",
	// 	"100000N001",
	// 	"1111111111",
	// 	NULL
	// };
	t_data	data;
	int fd;

	// data.map.map_data = map;
	fd = validate_arg(argc, argv);
    ft_memset(&data, 0, sizeof(t_data));
	if (parse_scene(fd, &data) != 0)
    {
        print_error("Parsing failed\n");
        return (1);
    }
    printf("%s\n%s\n%s\n%s\n", data.no_path, data.so_path, data.we_path, data.ea_path);

	free_data(&data);
	return (0);
}