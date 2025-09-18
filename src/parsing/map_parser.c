#include "cub3d.h"

int is_map(char *line)
{
    int     i;
    int     map_chars;

    map_chars = 0;
    i = 0;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == '1' || line[i] == '0' || line[i] == 'S' || 
            line[i] == 'N' || line[i] == 'E' || line[i] == 'W')
            map_chars = 1;
        else if (line[i] != ' ')
        {
            print_error("Invalid map character\n");   
            return (2);
        }
        i++;
    }
    return (map_chars);
}
