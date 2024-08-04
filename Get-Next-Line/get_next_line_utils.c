/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:25:07 by jlebre            #+#    #+#             */
/*   Updated: 2024/08/04 13:40:50 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

int	is_it_nline(char *buf)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (buf[j])
	{
		if (i)
			buf[k++] = buf[j];
		if (buf[j] == '\n')
			i = 1;
		buf[j++] = 0;
	}
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	if (size != 0 && nmemb > ((size_t)-1 / size))
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (i < nmemb * size)
		{
			*((char *)ptr + i) = 0;
			i++;
		}
	}
	return (ptr);
}

char	*my_line(char *line, char *buf)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = line;
	line = ft_calloc((ft_strlen(buf) + ft_strlen(line) + 1), sizeof(char));
	if (line == NULL)
		return (NULL);
	while (tmp && tmp[i])
	{
		line[i] = tmp[i];
		i++;
	}
	while (*buf)
	{
		if (*buf != '\n')
			line[i++] = *buf;
		if (*buf++ == '\n')
			break ;
	}
	line[i] = '\0';
	if (tmp != NULL)
		free(tmp);
	return (line);
}
