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

t_list	*parse_scene(int fd)
{
	t_list	*head_list;

	head_list = read_file_to_list(fd);
	if (head_list)
		return ;
}
