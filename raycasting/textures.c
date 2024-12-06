/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:36:32 by Apple             #+#    #+#             */
/*   Updated: 2024/12/06 09:35:10 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	ft_load_texture(t_data *data)
{
	data->north_texture = mlx_load_png(data->map->no_txt);
	if (!data->north_texture)
		clean_exit_pars(data, "Failed to load north texture", 42);
	data->south_texture = mlx_load_png(data->map->so_txt);
	if (!data->south_texture)
		clean_exit_pars(data, "Failed to load south texture", 43);
	data->east_texture = mlx_load_png(data->map->ea_txt);
	if (!data->east_texture)
		clean_exit_pars(data, "Failed to load east texture", 44);
	data->west_texture = mlx_load_png(data->map->we_txt);
	if (!data->west_texture)
		clean_exit_pars(data, "Failed to load west texture", 45);
	data->door_texture = mlx_load_png("images/textures/door.png");
	if (!data->door_texture)
		clean_exit_pars(data, "Failed to load door texture", 46);
}

static void	ft_nrm_drw_fc(t_data *data, int y, int *alpha)
{
	int	base_offset;
	int	adjust_value;

	if (data->light)
		base_offset = WIN_H / 6;
	else
		base_offset = WIN_H / 8;
	if (data->light)
		adjust_value = 80;
	else
		adjust_value = 165;
	*alpha = ((y - base_offset) * 255 / (WIN_H - base_offset)) - adjust_value;
	if (*alpha < 0)
		*alpha = 0;
	else if (*alpha > 255)
		*alpha = 255;
}

void	ft_drw_fc(t_data *data)
{
	int	y;
	int	x;
	int	color_floor;
	int	color_ceiling;
	int	alpha;

	color_floor = get_rgba(169, 169, 169, 255);
	color_ceiling = get_rgba(11, 25, 44, 255);
	y = -1;
	while (++y < WIN_H / 2)
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(data->win_img, x, y, color_ceiling);
	}
	y = (WIN_H / 2) - 1;
	while (++y < WIN_H)
	{
		ft_nrm_drw_fc(data, y, &alpha);
		color_floor = get_rgba(169, 169, 169, alpha);
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(data->win_img, x, y, color_floor);
	}
}

void	ft_drctn_bsd_txtr(t_data *data, int i)
{
	if (data->rays[i].door)
		data->applied_texture = data->door_texture;
	else if (data->rays[i].orn == 'h')
	{
		if (data->rays[i].is_up)
			data->applied_texture = data->north_texture;
		else
			data->applied_texture = data->south_texture;
	}
	else
	{
		if (data->rays[i].is_left)
			data->applied_texture = data->west_texture;
		else
			data->applied_texture = data->east_texture;
	}
}
