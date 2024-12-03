/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:41:09 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/03 21:25:26 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_turning_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->frame = NULL;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t)
			* TRN_ON_FRMS, 0);
	i = -1;
	while (++i < TRN_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin(
						"./images/turn_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit_init(data, "Can't load png", 14);
	}
}

void	init_idle_light_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = -1;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t)
			* IDLE_ON_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < IDLE_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin(
						"./images/idle_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit_init(data, "Can't load png", 45);
	}
}

void	init_turning_off_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t)
			* TRN_OFF_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < TRN_OFF_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin(
						"./images/turn_light_off/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit_init(data, "Can't load png", 51);
	}
}

void	init_walking_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t)
			* WALK_ON_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < WALK_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin(
						"./images/walk_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit_init(data, "Can't load png", 77);
	}
}

void	init_walking_off_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t)
			* WALK_OFF_FRMS, 0);
	anm->frame = NULL;
	txtr = mlx_load_png(ft_strjoin(ft_strjoin("./images/walk_light_off/f_",
					ft_itoa(anm->curr_frm)), ".png"));
	if (!txtr)
		clean_exit_init(data, "Can't load png", 88);
	anm->frame = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);
	i = -1;
	while (++i < WALK_OFF_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin(
						"./images/walk_light_off/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit_init(data, "Can't load png", 43);
	}
}
