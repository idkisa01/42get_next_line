/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabegar <isabegar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:56:50 by isabegar          #+#    #+#             */
/*   Updated: 2024/11/27 16:56:50 by isabegar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char		*_fill_line_buffer(int fd, char *left_c, char *buffer);
static char		*_set_line(char *line);

static char	*_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	size_t	bytes_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(left_c, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = left_c;
		left_c = ft_strjoin(left_c, buffer);
		free(temp);
	}
	free(buffer);
	return (left_c);
}
static char	*_set_line(char **left_c)
{
	char    *line;
    char    *temp;
    size_t  len;

    len = 0;
    while ((*left_c)[len] != '\n')
        len++;
    if ((*left_c)[len] == '\n')
        len++;
    line = ft_substr(*left_c, 0, len);
    temp = *left_c;
    *left_c = ft_strdup(&((*left_c)[len]));
    free(temp);
    return (line);
}
char	*get_next_line(int fd)
{
	static char *left_c;
	char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    left_c = _fill_line_buffer(fd, left_c);
    if (!left_c)
        return (NULL);
    line = _set_line(&left_c);
    if (!line || !*line)
    {
        free(line);
        return (NULL);
    }
    return (line);
}

#include <stdio.h>
int	main(void)
{
	char	*line;
	int		fd;

	fd = open("read.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s\n", line);
			free(line);
		}
		else
			break ;
	}
	close(fd);
	return (0);
}
