/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:06:50 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 18:15:16 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	delete_wall_txtrs(t_data *data)
{
	if (data->north_texture)
		mlx_delete_texture(data->north_texture);
	if (data->south_texture)
		mlx_delete_texture(data->south_texture);
	if (data->east_texture)
		mlx_delete_texture(data->east_texture);
	if (data->west_texture)
		mlx_delete_texture(data->west_texture);
	if (data->door_texture)
		mlx_delete_texture(data->door_texture);
}

static void	delete_anm_txtrs(t_data *data, int i)
{
	while (++i < TRN_ON_FRMS)
		if (data->trn_on_anm.txtrs[i])
			mlx_delete_texture(data->trn_on_anm.txtrs[i]);
	i = -1;
	while (++i < TRN_OFF_FRMS)
		if (data->trn_off_anm.txtrs[i])
			mlx_delete_texture(data->trn_off_anm.txtrs[i]);
	i = -1;
	while (++i < IDLE_ON_FRMS)
		if (data->idle_light_on_anm.txtrs[i])
			mlx_delete_texture(data->idle_light_on_anm.txtrs[i]);
	i = -1;
	while (++i < WALK_ON_FRMS)
		if (data->walk_light_on_anm.txtrs[i])
			mlx_delete_texture(data->walk_light_on_anm.txtrs[i]);
	i = -1;
	while (++i < WALK_OFF_FRMS)
		if (data->walk_light_off_anm.txtrs[i])
			mlx_delete_texture(data->walk_light_off_anm.txtrs[i]);
	mlx_delete_image(data->mlx, data->trn_on_anm.frame);
	mlx_delete_image(data->mlx, data->trn_off_anm.frame);
	mlx_delete_image(data->mlx, data->idle_light_on_anm.frame);
	mlx_delete_image(data->mlx, data->walk_light_on_anm.frame);
	mlx_delete_image(data->mlx, data->walk_light_off_anm.frame);
}

void	clean_exit(t_data *data, char *err, int stat)
{
	delete_wall_txtrs(data);
	mlx_delete_image(data->mlx, data->map->mnmap_img);
	mlx_delete_image(data->mlx, data->win_img);
	mlx_delete_image(data->mlx, data->map->border_img);
	mlx_delete_image(data->mlx, data->map->cross_img);
	mlx_delete_image(data->mlx, data->lighter_on);
	mlx_delete_image(data->mlx, data->lighter_off);
	mlx_delete_image(data->mlx, data->black_bg);
	if (data->map->cross_txt)
		mlx_delete_texture(data->map->cross_txt);
	if (data->map->border_txt)
		mlx_delete_texture(data->map->border_txt);
	delete_anm_txtrs(data, -1);
	ft_malloc(0, 1);
	if (stat)
		printf("Error\n%s\n", err);
	exit(stat);
}

void	clean_exit_pars(t_data *data, char *err, int stat)
{
	delete_wall_txtrs(data);
	ft_malloc(0, 1);
	printf("Error\n%s\n", err);
	exit(stat);
}

void	close_hook(void	*param)
{
	clean_exit((t_data *)param, "All good", 0);
}
