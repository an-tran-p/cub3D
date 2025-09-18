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

int parse_color_ids(char *line, int i, t_data *data)
{
    if (line[i] == 'F' && (line[i + 1] == ' ' || 
        line[i + 1] == '\n' || line[i + 1] == '\0'))
    {
        if (save_color(&data->f_color, line + i + 2) != 0)
            return (1);
    }
    else if (line[i] == 'C' && (line[i + 1] == ' ' || 
        line[i + 1] == '\n' || line[i + 1] == '\0'))
    {
        if (save_color(&data->c_color, line + i + 2) != 0)
            return (1);
    }
    else if (ft_isdigit(line[i + 1]))
        return (print_error("Missing space after color identifier\n"), 1);
    else
        return (print_error("Invalid color identifier\n"), 1);
    return (0);
}

int	parse_identifiers(t_list *head, t_data *data)
{
	t_list	*curr;
	char	*line;
	int		i;
    int     map_res;

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
        if (line[i] == 'N')
        {
            if (save_texture(&data->no_path, line, i, data) != 0)
                return (1);
        }
        else if (line[i] == 'S')
        {
            if (save_texture(&data->so_path, line, i, data) != 0)
                return (1);
        }
        else if (line[i] == 'W')
        {
            if (save_texture(&data->we_path, line, i, data) != 0)
                return (1);
        }
        else if (line[i] == 'E')
        {
            if (save_texture(&data->ea_path, line, i, data) != 0)
                return (1);
        }
        else if (line[i] == 'F' || line[i] == 'C')
        {
            if (parse_color_ids(line, i, data) != 0)
                return (1);
        }
		else
        {
            if (has_map_chars(line + i))
            {
                map_res = is_map(line + i);
                if (map_res == 1)
                {
                    data->map_start_node = curr;
                    break ;
                }
                else if (map_res == 2)
                    return (1);
            }
            else
                return (print_error("Missing or invalid identifier\n"), 1);
        }
		curr = curr->next;
	}
    if (data->f_color != (uint32_t)-1)
	    printf("F - %x\n", data->f_color);
    if (data->c_color != (uint32_t)-1)
	    printf("C - %x\n", data->c_color);
	return (0);
}
int check_required_elements(t_data *data)
{
    int has_error;

    has_error = 0;
    if (!data->no_path && print_error(MSG_MISSING_NO))
        has_error = 1;
    if (!data->so_path && print_error(MSG_MISSING_SO)) 
        has_error = 1;
    if (!data->ea_path && print_error(MSG_MISSING_EA))
        has_error = 1;
    if (!data->we_path && print_error(MSG_MISSING_WE))
        has_error = 1;
    if (data->f_color == (uint32_t)-1 && print_error(MSG_MISSING_F))
        has_error = 1;
    if (data->c_color == (uint32_t)-1 && print_error(MSG_MISSING_C))
        has_error = 1;
    return (has_error);
}

int	parse_scene(int fd, t_data *data)
{
	t_list	*head_list;

	head_list = read_file_to_list(fd);
    close(fd);
	if (!head_list)
		return (1);
	ft_memset(data, 0, sizeof(t_data));
	data->f_color = (uint32_t)-1;
	data->c_color = (uint32_t)-1;
	if (parse_identifiers(head_list, data) != 0)
	{
		ft_lstclear(&head_list, free);
		free_data(data);
		return (1);
    }
    if (check_required_elements(data) != 0)
    {
        ft_lstclear(&head_list, free);
		free_data(data);
		return (1);
    }
    if (data->map_start_node == NULL)
    {
        ft_lstclear(&head_list, free);
		free_data(data);
		return (print_error("Map is missing\n"), 1);
    }
    if (data->map_start_node != NULL)
        print_error("Map will be parsed!\n");
    // if (parse_map(data->map_start_node, data) != 0)
    // {
    //     ft_lstclear(&head_list, free);
	// 	free_data(data);
	// 	return (1);
    // }

	ft_lstclear(&head_list, free);
	return (0);
}
