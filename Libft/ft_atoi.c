/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:42:27 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/08 11:02:16 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + str[i++] - 48;
		if (n < 0 && sign == 1)
			return (-1);
		else if (n < 0 && sign == -1)
			return (0);
	}
	return (n * sign);
}
