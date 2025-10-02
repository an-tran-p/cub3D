/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:58:14 by ikozhina          #+#    #+#             */
/*   Updated: 2025/10/02 09:53:46 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*handle_buffer(char *buffer, char *line);
static int	read_to_buffer(int fd, char *buffer, char **line);
static char	*ft_strjoin_up_nl(char const *s1, char const *s2);

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (buffer[0] != '\0')
		{
			line = handle_buffer(buffer, line);
			if (!line || ft_strchr(line, '\n'))
				return (line);
		}
		status = read_to_buffer(fd, buffer, &line);
		if (status == 1)
			return (line);
		if (status == 0)
			return (NULL);
	}
}

static char	*handle_buffer(char *buffer, char *line)
{
	char	*ptr_newline;
	char	*temp;

	temp = line;
	line = ft_strjoin_up_nl(temp, buffer);
	free(temp);
	if (!line)
		return (NULL);
	ptr_newline = ft_strchr(buffer, '\n');
	if (ptr_newline)
		ft_memmove(buffer, ptr_newline + 1, ft_strlen(ptr_newline));
	else
		buffer[0] = '\0';
	return (line);
}

static int	read_to_buffer(int fd, char *buffer, char **line)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		buffer[0] = '\0';
		if (bytes_read == 0 && *line && **line)
			return (1);
		free(*line);
		*line = NULL;
		return (0);
	}
	buffer[bytes_read] = '\0';
	return (2);
}

static char	*ft_strjoin_up_nl(char const *s1, char const *s2)
{
	char	*new_str;
	char	*ptr_newline;
	size_t	i;
	size_t	len_s2;

	i = 0;
	if (s1 == NULL)
		s1 = "";
	ptr_newline = ft_strchr(s2, '\n');
	if (ptr_newline)
		len_s2 = ptr_newline - s2 + 1;
	else
		len_s2 = ft_strlen(s2);
	new_str = malloc(ft_strlen(s1) + len_s2 + 1);
	if (new_str == NULL)
		return (NULL);
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2 && (ptr_newline == NULL || s2 <= ptr_newline))
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}
