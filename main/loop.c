/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/05 12:35:07 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	safe_delete_img(t_data *data, mlx_image_t **img)
{
	mlx_delete_image(data->mlx, *img);
	*img = NULL;
}

void	render_animations(t_data *data)
{
	if (data->turning_on && !data->turning_off)
		anm_turn_light_on(data, &data->trn_on_anm, mlx_get_time() * 1e3);
	else if (data->turning_off)
		anm_turn_light_off(data, &data->trn_off_anm, mlx_get_time() * 1e3);
	if (data->mouse && !data->bigmap)
		handle_mouse(data);
	if ((!data->is_moving) && data->light && !data->turning_on && !data->turning_off)
		anm_idle_light_on(data, &data->idle_light_on_anm, mlx_get_time() * 1e3);
	else if (data->light && data->is_moving && !data->turning_on && !data->turning_off)
		anm_walk_light_on(data, &data->walk_light_on_anm, mlx_get_time() * 1e3);
	else if (!data->light && data->is_moving && !data->turning_on && !data->turning_off)
		anm_walk_light_off(data, &data->walk_light_off_anm, mlx_get_time() * 1e3);
}

// loop hook
void	ft_looper(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data->mouse)
		check_mouse_pos(data);
	if (data->bigmap)
	{
		draw_bigmap(data);
		return ;
	}
	is_plr_moving(data);
	render_animations(data);
	data->is_moving = false;
	if (!data->rendering || data->bigmap)
		return ;
	move_plr(data);
	raycasting(data);
	draw_mnmap(data, 0, 0);
	draw_mnmap_rays(data);
	draw_circle(data->map->mnmap_img, (MNMAP_W / 2), (MNMAP_H / 2), 3);
	check_wall(data, data->map->x, data->map->y);
	data->rendering = false;
}
