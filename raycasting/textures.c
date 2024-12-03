/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:36:32 by Apple             #+#    #+#             */
/*   Updated: 2024/12/03 21:20:41 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	ft_nrm_txt(char *msg)
{
	printf("%s", msg);
	exit(1);
}

void	delete_wall_txtrs(t_data *data)
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

void	ft_load_texture(t_data *data)
{
	data->north_texture = mlx_load_png("images/textures/north200.png");
	if (!data->north_texture)
		clean_exit_init(data, "Failed to load north texture", 42);
	data->south_texture = mlx_load_png("images/textures/south200.png");
	if (!data->south_texture)
		clean_exit_init(data, "Failed to load south texture", 43);
	data->east_texture = mlx_load_png("images/textures/east200.png");
	if (!data->east_texture)
		clean_exit_init(data, "Failed to load east texture", 44);
	data->west_texture = mlx_load_png("images/textures/west200.png");
	if (!data->west_texture)
		clean_exit_init(data, "Failed to load west texture", 45);
	data->door_texture = mlx_load_png("images/textures/door.png");
	if (!data->door_texture)
		clean_exit_init(data, "Failed to load door texture", 45);
}

void	ft_drw_fc(t_data *data)
{
	int	y;
	int	x;
	int	color_floor;
	int	color_ceiling;

	y = -1;
	x = -1;
	color_floor = get_rgba(169, 169, 169, 255);
	color_ceiling = get_rgba(135, 206, 235, 255);
	while (++y < WIN_H / 2)
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(data->win_img, x, y, color_ceiling);
	}
	y = WIN_H / 2 - 1;
	while (++y < WIN_H)
	{
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
