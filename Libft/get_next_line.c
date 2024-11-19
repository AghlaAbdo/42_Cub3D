/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:59:22 by aaghla            #+#    #+#             */
/*   Updated: 2024/11/19 10:26:56 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gl_strjoin(char *s1, char *s2, int rd)
{
	char	*str;
	int		i;

	if (!s1)
		s1 = "\0";
	i = gl_strlen(s1, 0);
	str = (char *)malloc((i + rd +1) * sizeof(char));
	if (!str)
	{
		if (s1[0])
			free(s1);
		return (NULL);
	}
	i = 0;
	rd = 0;
	while (s1[i])
		str[rd++] = s1[i++];
	i = 0;
	while (s2[i])
		str[rd++] = s2[i++];
	str[rd] = '\0';
	if (s1[0])
		free(s1);
	return (str);
}

static char	*gl_read_line(int fd, char *reached)
{
	char	*buff;
	int		rd;

	rd = 1;
	buff = malloc(((size_t)BUFFER_SIZE +1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!ft_strchr(reached, '\n') && rd > 0)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
		{
			if (reached)
				free(reached);
			return (free(buff), NULL);
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
	else if (!ft_strchr(reached, '\n'))
		return (free(reached), NULL);
	i = gl_strlen(reached, '\n');
	j = gl_strlen(reached, '\0');
	new = malloc((j - i) * sizeof(char));
	if (!new)
		return (free(reached), NULL);
	j = 0;
	i++;
	while (reached[i])
		new[j++] = reached[i++];
	new[j] = '\0';
	free(reached);
	if (!new[0])
		return (free(new), NULL);
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
