/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:22 by aaghla            #+#    #+#             */
/*   Updated: 2024/08/19 08:03:03 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gl_read_line(int fd, char *reached)
{
	char	*buff;
	int		rd;

	rd = 1;
	buff = malloc(((size_t)BUFFER_SIZE +1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!gl_strchr(reached, '\n') && rd > 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			if (reached)
				free(reached);
			return (gl_free_it(buff));
		}
		if (rd == 0)
			break ;
		buff[rd] = '\0';
		reached = gl_strjoin(reached, buff, rd);
	}
	free(buff);
	return (reached);
}

static char	*gl_one_line(char *reached)
{
	char	*line;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = -1;
	n = 1;
	if (!reached)
		return (NULL);
	while (reached[i] && reached[i] != '\n')
		i++;
	if (reached[i] == '\n')
		n = 2;
	line = malloc((i + n) * sizeof(char));
	if (!line)
		return (NULL);
	while (++j < i)
		line[j] = reached[j];
	if (n == 2)
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static char	*gl_next_line(char *reached)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!reached)
		return (NULL);
	else if (!gl_strchr(reached, '\n'))
		return (gl_free_it(reached));
	i = gl_strlen(reached, '\n');
	j = gl_strlen(reached, '\0');
	new = malloc((j - i) * sizeof(char));
	if (!new)
		return (gl_free_it(reached));
	j = 0;
	i++;
	while (reached[i])
		new[j++] = reached[i++];
	new[j] = '\0';
	free(reached);
	if (!new[0])
		return (gl_free_it(new));
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*reached;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reached = gl_read_line(fd, reached);
	line = gl_one_line(reached);
	reached = gl_next_line(reached);
	return (line);
}
