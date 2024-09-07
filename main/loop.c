/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/07 20:21:34 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// loop hook
void	ft_looper(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->mouse && !data->big_mnmap)
		handle_mouse(data);
	if (!data->mouse)
		check_mouse_pos(data);
	if (data->big_mnmap)
		draw_big_mnmap(data);
	if (!ab_is_moving(data) || data->big_mnmap)
		return ;
	plr_move(data);
	raycasting(data);
	draw_mnmap(data);
	draw_mnmap_rays(data);
	draw_circle(data->map->mnmap_img, (MNMAP_W / 2), (MNMAP_H / 2), 3);
	check_wall(data, data->plr->x, data->plr->y);
	data->is_moving = false;
}
