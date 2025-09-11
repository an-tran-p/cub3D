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
        curr = curr->next;
    }
    return (0);
}


int parse_scene(int fd, t_data *data)
{
	t_list	*head_list;

	head_list = read_file_to_list(fd);
	if (!head_list)
		return (1);
    
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
