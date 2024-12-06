/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:27:35 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/05 12:48:05 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char *s, unsigned int num, int sign)
{
	char	temp;
	int		start;
	int		end;

	start = 0;
	if (sign < 0)
		s[start++] = '-';
	while (num > 0)
	{
		s[start++] = num % 10 + 48;
		num /= 10;
	}
	s[start] = '\0';
	end = start - 1;
	start = 0;
	if (sign < 0)
		start++;
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}

static char	*minint(char *s, int n)
{
	unsigned int	num;

	num = (unsigned int)n;
	s = (char *)ft_malloc(12 * sizeof(char), 0);
	if (!s)
		return (NULL);
	swap(s, num, -1);
	return (s);
}

static int	sizeofn(int n)
{
	int	i;

	if (n < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*iszero(char *s)
{
	s = (char *)ft_malloc(2 * sizeof(char), 0);
	if (!s)
		return (NULL);
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		i;
	int		sign;

	sign = 1;
	number = NULL;
	i = 0;
	if (n == -2147483648)
		return (minint(number, n));
	if (n == 0)
		return (iszero(number));
	i = sizeofn(n);
	if (n < 0)
	{
		n = -n;
		sign = -sign;
		i++;
	}
	number = (char *)ft_malloc((i + 1) * sizeof(char), 0);
	if (!number)
		return (NULL);
	swap(number, n, sign);
	return (number);
}
