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

static char	*fill_line_buffer(int fd, char *buffer_storage, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		if (!buffer_storage)
			buffer_storage = ft_strdup("");
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(buffer_storage, buffer);
		free(buffer_storage);
		buffer_storage = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (buffer_storage);
}

char	*get_next_line(int fd)
{
	static char	*static_storage;
	char		*line;
	char		*buffer;
	char		*aux;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, static_storage, buffer);
	if (!line)
		return (free(static_storage), static_storage = NULL, NULL);
	aux = ft_strchr(line, '\n');
	if (aux && aux[1] != '\0')
	{
		static_storage = ft_strdup(aux +1);
		aux[1] = '\0';
	}
	else
		static_storage = NULL;
	return (line);
}
/*#include <stdio.h>
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
}*/
