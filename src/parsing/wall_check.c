#include "cub3d.h"

int build_map_grid(t_list *map_start_node, t_data *data)
{
    int i;
    char    **map;
    t_list  *curr;
    int  line_len;
    int j;
    char *line;

    map = ft_calloc(data->map.height + 1, sizeof(char *));
    if (!map)
        return (1);
    i = 0;
    curr = map_start_node;
    while (i < data->map.height && curr)
    {
        line = (char *)curr->content;
        map[i] = malloc(sizeof(char) * (data->map.width + 1));
        if (!map[i])
        {
            while (--i >= 0)
                free(map[i]);
            free(map);
            return (1);
        }
        line_len = ft_strlen(curr->content);
        j = 0;
        while (j < line_len && j < data->map.width)
        {
            map[i][j] = line[j];
            j++;
        }
        while (j < data->map.width)
        {
            map[i][j] = ' ';
            j++;
        }
        map[i][data->map.width] = '\0';
        i++;
        curr = curr->next;
    }
    data->map.map_data = map;
    printf("%s\n", data->map.map_data[0]);
    printf("%s\n", data->map.map_data[1]);
    return (0);
}
