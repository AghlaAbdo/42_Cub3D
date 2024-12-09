/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 23:01:48 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// loop hook
void	ft_looper(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	is_plr_moving(data);
	data->is_moving = false;
	if (!data->rendering)
		return ;
	move_plr(data);
	raycasting(data);
	data->rendering = false;
}
