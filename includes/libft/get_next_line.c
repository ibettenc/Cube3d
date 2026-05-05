/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:19:06 by ibettenc          #+#    #+#             */
/*   Updated: 2025/11/11 17:44:35 by ibettenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*stash_read(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free_stash(&stash);
			return (NULL);
		}
		buffer[bytes] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	size_t	len;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
	{
		free_stash(&stash);
		return (NULL);
	}
	ft_strlcpy(line, stash, len + 1);
	return (line);
}

char	*clean_stash(char *stash)
{
	size_t	start;
	char	*new_stash;
	size_t	len;

	if (!stash || !*stash)
	{
		free_stash(&stash);
		return (NULL);
	}
	start = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (stash[start] == '\0')
		return (free_stash(&stash), NULL);
	start++;
	len = ft_strlen(stash + start);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free_stash(&new_stash), NULL);
	ft_strlcpy(new_stash, stash + start, len + 1);
	free_stash(&stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = stash_read(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
