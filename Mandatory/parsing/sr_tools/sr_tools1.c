/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sr_tools1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:42:29 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 09:42:30 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/cub3d.h"

int	sr_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*sr_dup(char *s)
{
	char	*tp;
	size_t	lenx;
	size_t	i;

	i = 0;
	lenx = sr_len(s);
	tp = (char *) ft_malloc(lenx + 1, 0);
	if (!tp)
		return (NULL);
	while (s[i])
	{
		*(tp + i) = *(s + i);
		i++;
	}
	tp[i] = '\0';
	return (tp);
}

char	*sr_substr(char *s, int start, int len)
{
	char	*substring;
	int		i;

	if (!s)
		return (NULL);
	if (start > sr_len(s))
		return (sr_dup(""));
	if (len > sr_len(s + start))
		len = sr_len(s + start);
	i = 0;
	substring = ft_malloc((len * sizeof(char)) + 1, 0);
	if (!substring)
		return (NULL);
	while (s[start] && i < len)
	{
		substring[i] = s[start];
		start++;
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

int	sr_strcmp( char *s1, char *s2)
{
	unsigned char	*ss1;
	unsigned char	*ss2;
	size_t			i;

	i = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (ss1[i] || ss2[i])
	{
		if (ss1[i] != ss2[i])
			return (0);
		i++;
	}
	if (sr_len(s1) == sr_len(s2))
		return (1);
	return (0);
}

void	sr_rmv_nline(char *str)
{
	size_t	len;

	len = sr_len(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
