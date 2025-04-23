/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:11:39 by alfavre           #+#    #+#             */
/*   Updated: 2025/02/09 20:35:15 by alfavre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Join the old buffer and the new buffer and free the old buffer. If
 * the old buffer doesn't exit, join an empty string with the new buffer.
 * @param buffer The old buffer
 * @param reader The new buffer
 * @return The result of the join of the 2 parameters. NULL if the malloc of
 * ft_strjoin didn't work.
 */
static char	*ft_join_and_free(char *buffer, char *readed)
{
	char	*temp;

	if (!buffer)
		return (ft_strjoin("", readed));
	temp = ft_strjoin(buffer, readed);
	free(buffer);
	return (temp);
}

/**
 * @brief Read the file descriptor and put the result in the buffer. If there
 * is already a string in the buffer, join the new buffer with the old one.
 * Read until there is no more things to read or if there is a \n.
 * @param fd The file descriptor to read
 * @param buffer The static buffer readed with the BUFFER_SIZE
 * @return The new buffer with the old buffer and the new buffer join.
 */
static char	*ft_read_file(int fd, char *buffer)
{
	char	*readed;
	ssize_t	bytes_read;

	readed = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readed)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, readed, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(readed), NULL);
		if (bytes_read == 0)
			return (free(readed), buffer);
		readed[bytes_read] = '\0';
		buffer = ft_join_and_free(buffer, readed);
		if (ft_strchr(readed, '\n'))
			break ;
	}
	free(readed);
	return (buffer);
}

/**
 * @brief Fill the line to write to the output including the \\n
 * if there is one.
 * @param buffer The static buffer
 * @return The string to write to the output
 */
static char	*ft_fill_line(char *buffer)
{
	char	*line;
	int		index;
	int		size;

	index = 0;
	if (!buffer[index])
		return (NULL);
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (buffer[index] == '\n')
		size = index + 2;
	else
		size = index + 1;
	line = malloc(sizeof(char) * size);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, size);
	return (line);
}

/**
 * @brief Buffer management to keep only what is after
 * the '\n' if there is one. Free the old buffer.
 * @param buffer The old buffer
 * @return NULL if it's the end of the file. The part of
 * the old buffer after the '\n'.
 */
static char	*ft_rest(char *buffer)
{
	char	*rest;
	int		index;
	int		size;

	index = 0;
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (!buffer[index])
		return (free(buffer), NULL);
	size = ft_strlen(buffer) - index - 1;
	if (size == 0)
		return (free(buffer), NULL);
	rest = malloc(sizeof(char) * (size + 1));
	if (!rest)
		return (free(buffer), NULL);
	ft_strlcpy(rest, buffer + index + 1, size + 1);
	free(buffer);
	return (rest);
}

/**
 * @brief Read a file descriptor until the next '\n'
 * @param fd The file descriptor to read
 * @return The line content. NULL if there is an error or there is no 
 * more to read.
 */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = ft_read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (free(buffer[fd]), NULL);
	line = ft_fill_line(buffer[fd]);
	buffer[fd] = ft_rest(buffer[fd]);
	return (line);
}
