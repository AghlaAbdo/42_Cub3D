/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:49:38 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/04 18:01:19 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_imgs_null(t_data *data)
{
	data->lighter_on = NULL;
	data->lighter_off = NULL;
	data->map->mnmap_img = NULL;
	data->win_img = NULL;
	data->map->cross_img = NULL;
	data->map->cross_txt = NULL;
	data->map->border_img = NULL;
	data->map->border_txt = NULL;
	data->bigmap_img = NULL;
	data->lighter_on = NULL;
	data->lighter_off = NULL;
	data->black_bg = NULL;
}

static void	set_txtrs_null(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TRN_ON_FRMS)
		data->trn_on_anm.txtrs[i] = NULL;
	data->trn_on_anm.frame = NULL;
	i = -1;
	while (++i < TRN_OFF_FRMS)
		data->trn_off_anm.txtrs[i] = NULL;
	data->trn_off_anm.frame = NULL;
	i = -1;
	while (++i < IDLE_ON_FRMS)
		data->idle_light_on_anm.txtrs[i] = NULL;
	data->idle_light_on_anm.frame = NULL;
	i = -1;
	while (++i < WALK_ON_FRMS)
		data->walk_light_on_anm.txtrs[i] = NULL;
	data->walk_light_on_anm.frame = NULL;
	i = -1;
	while (++i < WALK_OFF_FRMS)
		data->walk_light_off_anm.txtrs[i] = NULL;
	data->walk_light_off_anm.frame = NULL;
	set_imgs_null(data);
}

static void	allocate_memory(t_data *data)
{
	data->map = ft_malloc(sizeof(t_map), 0);
	data->plr = ft_malloc(sizeof(t_player), 0);
	data->trn_on_anm.txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t)
			* TRN_ON_FRMS, 0);
	data->trn_off_anm.txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t)
			* TRN_OFF_FRMS, 0);
	data->idle_light_on_anm.txtrs = (mlx_texture_t **)ft_malloc(
			sizeof(mlx_texture_t) * IDLE_ON_FRMS, 0);
	data->walk_light_on_anm.txtrs = (mlx_texture_t **)ft_malloc(
			sizeof(mlx_image_t) * WALK_ON_FRMS, 0);
	data->walk_light_off_anm.txtrs = (mlx_texture_t **)ft_malloc(
			sizeof(mlx_image_t) * WALK_OFF_FRMS, 0);
}

void	ab_set_orn(t_data *data)
{
	if (data->plr->orn == 'E')
		data->plr->rot_angl = 0;
	else if (data->plr->orn == 'S')
		data->plr->rot_angl = M_PI / 2;
	else if (data->plr->orn == 'W')
		data->plr->rot_angl = M_PI;
	else if (data->plr->orn == 'N')
		data->plr->rot_angl = M_PI + (M_PI / 2);
}

void	init_data(t_data *data)
{
	allocate_memory(data);
	data->map->c[0] = -1;
	data->map->f[0] = -1;
	data->map->ea_txt = NULL;
	data->map->so_txt = NULL;
	data->map->we_txt = NULL;
	data->map->no_txt = NULL;
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->door_texture = NULL;
	data->map->plr_nb = 0;
	data->map->row = 0;
	data->is_moving = true;
	data->rendering = true;
	data->light = false;
	data->mouse = false;
	data->bigmap = false;
	data->turning_on = false;
	data->turning_off = false;
	data->idle_on = false;
	data->walking_on = false;
	data->walking_off = false;
	set_txtrs_null(data);
}
