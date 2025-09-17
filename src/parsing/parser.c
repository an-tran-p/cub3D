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

int	parse_identifiers(t_list *head, t_data *data)
{
	t_list	*curr;
	char	*line;
	int		i;

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
		if (ft_isdigit(line[i])) // need better check for map start
			break ;
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
		else if (line[i] == 'F' && line[i + 1] == ' ')
        {
            if (save_color(&data->f_color, line + i + 1))
			    return (1);
        }
		else if (line[i] == 'C' && line[i + 1] == ' ')
        {
            if (save_color(&data->c_color, line + i + 1))
			    return (1);
        }
		else
			return (print_error("Missing or invalid identifier\n"), 1);
		curr = curr->next;
	}
	printf("%x\n%x\n", data->f_color, data->c_color);
	return (0);
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
	if (parse_identifiers(head_list, data) == 1)
	{
		ft_lstclear(&head_list, free);
		free_data(data);
		close(fd);
		return (1);
	}
	ft_lstclear(&head_list, free);
	if (!data->no_path || !data->so_path || !data->ea_path || !data->we_path)
		return (print_error(MSG_TEXTURE_MISSING), 1);
	if (data->f_color == (uint32_t)-1 || data->c_color == (uint32_t)-1)
		return (print_error(MSG_COLOR_MISSING), 1);
	return (0);
}
