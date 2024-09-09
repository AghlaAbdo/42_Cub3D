/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/09 19:33:52 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anm_light_on(t_data *data, t_animation *anm, double curr_time)
{
	if (curr_time - anm->last_frm_time > FRM_DUR)
	{
		anm->frames[anm->curr_frm]->enabled = false;
		anm->frames[(anm->curr_frm + 1) % TRN_ON_FRMS]->enabled = true;
		anm->curr_frm = (anm->curr_frm + 1) % TRN_ON_FRMS;
		anm->last_frm_time = curr_time;
	}
	if (anm->curr_frm == 7)
	{
		data->light = true;
		data->is_moving = true;
	}
	if (anm->curr_frm == TRN_ON_FRMS - 1)
	{
		data->turning_on = false;
		anm->frames[TRN_ON_FRMS - 1]->enabled = false;
	}
}

void	anm_idle_light_on(t_data *data, t_animation *anm, double curr_time)
{
	if (curr_time - anm->last_frm_time > FRM_DUR + 40)
	{
		anm->frames[anm->curr_frm]->enabled = false;
		anm->frames[(anm->curr_frm + 1) % IDLE_ON_FRMS]->enabled = true;
		anm->curr_frm = (anm->curr_frm + 1) % IDLE_ON_FRMS;
		anm->last_frm_time = curr_time;
	}
}

void	anm_turn_off(t_data *data, t_animation *anm, double curr_time)
{
	if (curr_time - anm->last_frm_time > FRM_DUR)
	{
		anm->frames[anm->curr_frm]->enabled = false;
		anm->frames[(anm->curr_frm + 1) % TRN_OFF_FRMS]->enabled = true;
		anm->curr_frm = (anm->curr_frm + 1) % TRN_OFF_FRMS;
		anm->last_frm_time = curr_time;
	}
	if (anm->curr_frm == 7)
	{
		data->light = false;
		data->is_moving = true;
	}
	if (anm->curr_frm == TRN_OFF_FRMS - 1)
	{
		data->turning_off = false;
		
	}
}

// loop hook
void	ft_looper(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->turning_on)
		anm_light_on(data, &data->trn_on_anm, mlx_get_time() * 1e3);
	if (data->turning_off)
		anm_turn_off(data, &data->trn_off_anm, mlx_get_time() * 1e3);
	if (!data->turning_on && !data->is_moving && data->light && !data->turning_off)
		anm_idle_light_on(data, &data->idle_light_on_anm, mlx_get_time() * 1e3);
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
