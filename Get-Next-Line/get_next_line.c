/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:45:12 by ksohail-          #+#    #+#             */
/*   Updated: 2024/10/08 11:54:48 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gcl(char *remains, char *buffer)
{
	char			*array;
	unsigned int	size;
	int				i;
	int				j;

	if (!remains && !buffer)
		return (NULL);
	size = ft_strlen(remains) + ft_strlen(buffer);
	array = (char *)malloc(sizeof(char) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	if (remains)
	{
		while (remains[i])
			array[j++] = remains[i++];
		i = 0;
	}
	while (buffer[i])
		array[j++] = buffer[i++];
	array[size] = '\0';
	free((void *)remains);
	return (array);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*remains;
	char		*line;
	int			count;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[0] = '\0';
	count = 1;
	while (!find_new_line(buffer) && count != 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (NULL);
		buffer[count] = '\0';
		remains = ft_strjoin_gcl(remains, buffer);
	}
	line = push_line(remains);
	remains = cut_next_line(remains);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
