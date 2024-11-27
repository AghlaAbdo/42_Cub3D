/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/11/27 15:30:23 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	anm_turn_light_on(t_data *data, t_animation *anm, double curr_time)
{
	mlx_texture_t	*txtr;

	if (curr_time - anm->last_frm_time > FRM_DUR)
	{
		if (data->walking_off)
		{
			mlx_delete_image(data->mlx, data->walk_light_off_anm.frame);
			data->walk_light_off_anm.frame = NULL;
		}
		if (data->walk_light_off_anm.frame)
			mlx_delete_image(data->mlx, data->walk_light_off_anm.frame);
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
		mlx_delete_image(data->mlx, anm->frame);
		anm->frame = NULL;
	}
}

void	anm_idle_light_on(t_data *data, t_animation *anm, double curr_time)
{
	mlx_texture_t	*txtr;
	if (curr_time - anm->last_frm_time > FRM_DUR + 40)
	{
		if (!data->idle_on)
			data->idle_on = true;
		if (data->walking_on)
		{
			mlx_delete_image(data->mlx, data->walk_light_on_anm.frame);
			data->walk_light_on_anm.frame = NULL;
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
		{
			mlx_delete_image(data->mlx, data->walk_light_on_anm.frame);
			data->walk_light_on_anm.frame = NULL;
		}
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
		mlx_delete_image(data->mlx, anm->frame);
		anm->frame = NULL;
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
			mlx_delete_image(data->mlx, data->idle_light_on_anm.frame);
			data->idle_light_on_anm.frame = NULL;
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
			mlx_delete_image(data->mlx, data->trn_off_anm.frame);
		if (anm->frame)
			mlx_delete_image(data->mlx, anm->frame);
		anm->curr_frm = (anm->curr_frm + 1) % WALK_OFF_FRMS;
		anm->frame = mlx_texture_to_image(data->mlx, anm->txtrs[anm->curr_frm]);
		mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
		anm->last_frm_time = curr_time;
	}
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
	if (data->turning_on && !data->turning_off)
		anm_turn_light_on(data, &data->trn_on_anm, mlx_get_time() * 1e3);
	else if (data->turning_off)
		anm_turn_light_off(data, &data->trn_off_anm, mlx_get_time() * 1e3);
	if (data->mouse && !data->bigmap)
		handle_mouse(data);
	ab_is_moving(data);
	if ((!data->is_moving) && data->light && !data->turning_on && !data->turning_off)
		anm_idle_light_on(data, &data->idle_light_on_anm, mlx_get_time() * 1e3);
	else if (data->light && data->is_moving && !data->turning_on && !data->turning_off)
		anm_walk_light_on(data, &data->walk_light_on_anm, mlx_get_time() * 1e3);
	else if (!data->light && data->is_moving  && !data->turning_on && !data->turning_off)
		anm_walk_light_off(data, &data->walk_light_off_anm, mlx_get_time() * 1e3);
	data->is_moving = false;
	if (!data->rendering || data->bigmap)
		return ;
	plr_move(data);
	raycasting(data);
	draw_mnmap(data);
	draw_mnmap_rays(data);
	draw_circle(data->map->mnmap_img, (MNMAP_W / 2), (MNMAP_H / 2), 3);
	check_wall(data, data->map->x, data->map->y);
	data->rendering = false;
}
