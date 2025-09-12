#include "cub3d.h"

t_list	*read_file_to_list(int fd)
{
	char	*line;
	t_list	*node;
	t_list	*head;

	head = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
	}
	return (head);
}
int    save_path(char **path, char *line)
{
    int     i;

    i = 0;
    while (line[i] == ' ')
        i++;
    if (*path)
    {
        print_error("Similar texture identifies\n");
        return (1);
    }
    *path = ft_strdup(line + i);
    if (!(*path))
    {
        print_error("Malloc failed\n");
        return (1);
    }
    return (0);
}
uint32_t get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int validate_rgb_format(char *line)
{
    int i;
    int comma_count;
    int digit_num;

    i = 0;
    comma_count = 0;
    digit_num = 0;
    
    while (line[i] == ' ')
        i++;

    while (line[i] && line[i] != '\n')
    {
        if (ft_isdigit(line[i]))
        {
            while (line[i] && ft_isdigit(line[i]))
                i++;
            digit_num++;
        }
        else if (line[i] == ',')
        {
            comma_count++;
            i++;
        }
        else if (line[i] == ' ')
            i++;
        else
        {
            print_error("Invalid RGB: invalid character\n");
            return (1);
        }    
    }
    if (digit_num != 3)
    {
        print_error("Invalid RGB: expected 3 numbers\n");
        return (1);
    }
    if (comma_count != 2)
    {
        print_error("Invalid RGB: expected two commas\n");
        return (1);
    }
    return (0);
}

int save_color(uint32_t	*color, char *line)
{
    int i;
    int r;
    int g;
    int b;

    if (*color != (uint32_t)-1)
    {
        print_error("Duplicate color identifier\n");
        return (1);
    }
    if (validate_rgb_format(line) != 0)
        return (1);
    i = 0;
    while(line[i] == ' ' && line[i])
        i++;
    r = ft_atoi(line + i);
    if (r < 0 || r > 255)
    {
        print_error("Invalid RGB: R is outside the range 0-255\n");
        return (1);
    }
    while(ft_isdigit(line[i]) && line[i])
        i++;
    while(line[i] != ',' && line[i])
        i++;
    if (line[i] == ',')
        i++;
    while(line[i] == ' ' && line[i])
        i++;
    g = ft_atoi(line + i);
    if (g < 0 || g > 255)
    {
        print_error("Invalid RGB: G is outside range 0-255\n");
        return (1);
    }
    while(ft_isdigit(line[i]) && line[i])
        i++;
    while(line[i] != ',' && line[i])
        i++;
    if (line[i] == ',')
        i++;
    while(line[i] == ' ' && line[i])
        i++;
    b = ft_atoi(line + i);
    if (b < 0 || b > 255)
    {
        print_error("Invalid RGB: B is outside range 0-255\n");
        return (1);
    }
    *color = get_rgba(r, g, b, 255);
    printf("%d, %d, %d\n", r, g, b);
    return (0);
}

int    parse_paths(t_list *head, t_data *data)
{
    t_list *curr;
    char    *line;
    int     i;

    curr = head;
    while (curr)
    {
        i = 0;
        line = (char *)curr->content;
        if (line[0] == '\n' || line[0] == '\0')
        {
            curr = curr->next;
            continue ;
        }
        while (line[i] == ' ')
            i++;
        if (ft_isdigit(line[i])) //need better check for map start
            break ;
        if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
        {
            if (save_path(&data->no_path, line + (i + 2)) != 0)
                return (1);
        }
        else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
        {
            if (save_path(&data->so_path, line + (i + 2)) != 0)
                return (1);
        }
        else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
        {
            if (save_path(&data->we_path, line + (i + 2)) != 0)
                return (1);
        }
        else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
        {
            if (save_path(&data->ea_path, line + (i + 2)) != 0)
                return (1);
        }
        else if (line[i] == 'F' && line[i + 1] == ' ')
        {
            if (save_color(&data->f_color, line + (i + 1)) != 0)
                return (1);
        }
        else if (line[i] == 'C' && line[i + 1] == ' ')
        {
            if (save_color(&data->c_color, line + (i + 1)) != 0)
                return (1);
        }
        curr = curr->next;
    }
    printf("%x\n%x\n", data->f_color, data->c_color);
    return (0);
}


int parse_scene(int fd, t_data *data)
{
	t_list	*head_list;

	head_list = read_file_to_list(fd);
	if (!head_list)
		return (1);
    ft_memset(&data, 0, sizeof(t_data));
    data->f_color = (uint32_t)-1;
    data->c_color = (uint32_t)-1;
    if (parse_paths(head_list, data) == 1)
    {
        ft_lstclear(&head_list, free);
        free_data(data);
        close(fd);
        return (1);
    }
    ft_lstclear(&head_list, free);
    close(fd);
    return (0);
}
