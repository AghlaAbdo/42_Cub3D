/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:42:44 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/10 18:31:46 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

void	ft_load_texture(t_data *data)
{
	data->north_texture = mlx_load_png(data->map->no_txt);
	if (!data->north_texture || data->north_texture->width != 1024
		| data->north_texture->height != 1024)
		clean_exit_pars(data, "Failed to load north texture", 42);
	data->south_texture = mlx_load_png(data->map->so_txt);
	if (!data->south_texture || data->south_texture->width != 1024
		|| data->south_texture->height != 1024)
		clean_exit_pars(data, "Failed to load south texture", 43);
	data->east_texture = mlx_load_png(data->map->ea_txt);
	if (!data->east_texture || data->east_texture->width != 1024
		|| data->east_texture->height != 1024)
		clean_exit_pars(data, "Failed to load east texture", 44);
	data->west_texture = mlx_load_png(data->map->we_txt);
	if (!data->west_texture || data->west_texture->width != 1024
		|| data->west_texture->height != 1024)
		clean_exit_pars(data, "Failed to load west texture", 45);
	data->door_texture = mlx_load_png("./Bonus/images/textures/door_1024.png");
	if (!data->door_texture || data->door_texture->width != 1024
		|| data->door_texture->height != 1024)
		clean_exit_pars(data, "Failed to load door texture", 45);
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
	int	clr_flr;
	int	clr_ceil;
	int	alpha;

	clr_ceil = get_rgba(data->map->c[0], data->map->c[1], data->map->c[2], 255);
	y = -1;
	while (++y < WIN_H / 2)
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(data->win_img, x, y, clr_ceil);
	}
	y = (WIN_H / 2) - 1;
	while (++y < WIN_H)
	{
		ft_nrm_drw_fc(data, y, &alpha);
		clr_flr = get_rgba(data->map->f[0], data->map->f[1],
				data->map->f[2], alpha);
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(data->win_img, x, y, clr_flr);
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
