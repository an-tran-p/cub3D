#include "cub3d.h"

int is_map(char *line)
{
    int i;
    int map_chars;

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

int get_line_length(char *line)
{
    int last_index;

    last_index = ft_strlen(line) - 1;
    while (last_index >= 0 && (line[last_index] == '\n' || line[last_index] == ' '))
        last_index--;
    return (last_index + 1);
}

int parse_map(t_list *map_start_node, t_data *data)
{
    t_list *curr;
    int max_width;
    int num_lines;
    char *line;
    int has_empty_line;
    int res_map;
    int line_len;

    curr = map_start_node;
    has_empty_line = 0;
    max_width = 0;
    num_lines = 0;
    while (curr)
    {
        line = (char *)curr->content;
        res_map = is_map(line);
        if (!res_map)
            has_empty_line++;
        else if (res_map == 2)
            return (1);
        else if (res_map == 1)
        {
            if (has_empty_line)
                return (print_error("Map can't be separated by empty lines\n"), 1);
        }
        num_lines++;
        line_len = get_line_length(line);
        if (max_width < line_len)
            max_width = line_len;
        curr = curr->next;
    }
    data->map.height = num_lines - has_empty_line;
    data->map.width = max_width;
    printf("width - %d\n", data->map.width);
    printf("height - %d\n", data->map.height);
    return (0);
}
