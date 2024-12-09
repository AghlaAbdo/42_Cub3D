/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:33:58 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 18:15:05 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	switch_light(t_data *data)
{
	if (!data->turning_on && data->light)
	{
		if (data->idle_on)
		{
			mlx_delete_image(data->mlx, data->idle_light_on_anm.frame);
			data->idle_light_on_anm.frame = NULL;
		}
		data->turning_off = true;
		data->lighter_on->enabled = false;
		data->lighter_off->enabled = true;
	}
	else if (!data->light)
	{
		data->turning_on = true;
		data->lighter_off->enabled = false;
		data->lighter_on->enabled = true;
	}
}

static void	draw_shade_bg(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			mlx_put_pixel(data->shade_bg, x, y, get_rgba(0, 0, 0, 120));
		}
	}
}

void	show_big_map(t_data *data)
{
	data->bigmap = true;
	data->map->mnmap_img->enabled = false;
	data->map->border_img->enabled = false;
	data->shade_bg = mlx_new_image(data->mlx, WIN_W, WIN_H);
	draw_shade_bg(data);
	data->bigmap_img = mlx_new_image(data->mlx, BIGMAP_W, BIGMAP_H);
	data->map->cross_img = mlx_texture_to_image(data->mlx,
			data->map->cross_txt);
	if (!data->shade_bg || !data->bigmap_img || !data->map->cross_img)
		clean_exit(data, "Can't create image", 50);
	if (mlx_image_to_window(data->mlx, data->shade_bg, 0, 0) == -1
		|| mlx_image_to_window(data->mlx, data->bigmap_img,
			WIN_W / 2 - BIGMAP_W / 2, WIN_H / 2 - BIGMAP_H / 2) == -1
		|| mlx_image_to_window(data->mlx, data->map->cross_img,
			WIN_W / 2 - BIGMAP_W / 2, WIN_H / 2 - BIGMAP_H / 2) == -1)
		clean_exit(data, "Can't put image to window", 51);
	data->map->bigmap_y = data->map->y;
	data->map->bigmap_x = data->map->x;
	data->map->bigmap_py = BIGMAP_H / 2;
	data->map->bigmap_px = BIGMAP_W / 2;
}

void	hide_big_map(t_data *data)
{
	data->bigmap = false;
	mlx_delete_image(data->mlx, data->bigmap_img);
	mlx_delete_image(data->mlx, data->shade_bg);
	mlx_delete_image(data->mlx, data->map->cross_img);
	data->map->mnmap_img->enabled = true;
	data->map->border_img->enabled = true;
	data->rendering = true;
}

void	handle_events(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		clean_exit(param, "all good", 0);
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS
		&& !data->bigmap)
		switch_light(data);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		if (!data->bigmap)
			mlx_set_mouse_pos(data->mlx, WIN_W / 2, WIN_H / 2);
		data->ms_x = WIN_W / 2;
		data->mouse = !data->mouse;
		if (!data->mouse)
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		data->bigmap = !data->bigmap;
		if (data->bigmap)
			show_big_map(data);
		else
			hide_big_map(data);
	}
}
