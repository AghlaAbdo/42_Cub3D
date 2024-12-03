/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:34:51 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/03 10:20:03 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anm_turn_light_on(t_data *data, t_animation *anm, double curr_time)
{
	if (curr_time - anm->last_frm_time > FRM_DUR)
	{
		if (data->walk_light_off_anm.frame)
			safe_delete_img(data, &data->walk_light_off_anm.frame);
		if (anm->frame)
			mlx_delete_image(data->mlx, anm->frame);
		anm->curr_frm = (anm->curr_frm + 1) % TRN_ON_FRMS;
		anm->frame = mlx_texture_to_image(data->mlx, anm->txtrs[anm->curr_frm]);
		if (anm->curr_frm != TRN_ON_FRMS - 1)
			mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
		anm->last_frm_time = curr_time;
	}
	if (anm->curr_frm == 7)
	{
		data->light = true;
		data->rendering = true;
	}
	if (anm->curr_frm == TRN_ON_FRMS - 1)
	{
		data->turning_on = false;
		safe_delete_img(data, &anm->frame);
	}
}

void	anm_idle_light_on(t_data *data, t_animation *anm, double curr_time)
{
	if (curr_time - anm->last_frm_time > FRM_DUR + 40)
	{
		if (!data->idle_on)
			data->idle_on = true;
		if (data->walking_on)
		{
			safe_delete_img(data, &data->walk_light_on_anm.frame);
			data->walking_on = false;
		}
		if (anm->frame)
			mlx_delete_image(data->mlx, anm->frame);
		anm->curr_frm = (anm->curr_frm + 1) % IDLE_ON_FRMS;
		anm->frame = mlx_texture_to_image(data->mlx, anm->txtrs[anm->curr_frm]);
		mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
		anm->last_frm_time = curr_time;
	}
}

void	anm_turn_light_off(t_data *data, t_animation *anm, double curr_time)
{
	mlx_texture_t	*txtr;

	if (curr_time - anm->last_frm_time > FRM_DUR)
	{
		if (data->walking_on)
			safe_delete_img(data, &data->walk_light_on_anm.frame);
		if (anm->frame)
			mlx_delete_image(data->mlx, anm->frame);
		anm->curr_frm = (anm->curr_frm + 1) % TRN_OFF_FRMS;
		anm->frame = mlx_texture_to_image(data->mlx, anm->txtrs[anm->curr_frm]);
		mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
		anm->last_frm_time = curr_time;
	}
	if (anm->curr_frm == 7)
	{
		data->light = false;
		data->rendering = true;
	}
	if (anm->curr_frm == TRN_OFF_FRMS - 1)
	{
		data->turning_off = false;
		safe_delete_img(data, &anm->frame);
		data->rendering = true;
		data->is_moving = true;
	}
}

void	anm_walk_light_on(t_data *data, t_animation *anm, double curr_time)
{
	mlx_texture_t	*txtr;

	if (curr_time - anm->last_frm_time > FRM_DUR)
	{
		if (!data->walking_on)
			data->walking_on = true;
		if (data->idle_on)
		{
			safe_delete_img(data, &data->idle_light_on_anm.frame);
			data->idle_on = false;
		}
		if (anm->frame)
			mlx_delete_image(data->mlx, anm->frame);
		anm->curr_frm = (anm->curr_frm + 1) % WALK_ON_FRMS;
		anm->frame = mlx_texture_to_image(data->mlx, anm->txtrs[anm->curr_frm]);
		mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
		anm->last_frm_time = curr_time;
	}
}

void	anm_walk_light_off(t_data *data, t_animation *anm, double curr_time)
{
	mlx_texture_t	*txtr;

	if (curr_time - anm->last_frm_time > FRM_DUR - 20)
	{
		if (!data->walking_off)
			data->walking_off = true;
		if (data->trn_off_anm.frame)
			safe_delete_img(data, &data->trn_off_anm.frame);
		if (anm->frame)
			mlx_delete_image(data->mlx, anm->frame);
		anm->curr_frm = (anm->curr_frm + 1) % WALK_OFF_FRMS;
		anm->frame = mlx_texture_to_image(data->mlx, anm->txtrs[anm->curr_frm]);
		mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
		anm->last_frm_time = curr_time;
	}
}
