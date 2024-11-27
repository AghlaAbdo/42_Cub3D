/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:17:28 by aaghla            #+#    #+#             */
/*   Updated: 2024/11/27 13:38:17 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mouse_pos(int ms_x, int ms_y, int x, int y)
{
	int	r;
	int	dx;
	int	dy;

	r = MNMAP_W / 2;
	dx = ms_x - x;
	dy = ms_y - y;
	if (dx * dx + dy * dy <= r * r)
		return (1);
	return (0);
}
static int	mouse_over_cross_icon(int x, int y)
{
	if (x >= WIN_W / 2 - BIGMAP_W / 2 && x <= WIN_W / 2 - BIGMAP_W / 2 + 40
		&& y >= WIN_H / 2 - BIGMAP_H / 2 && y <= WIN_H / 2 - BIGMAP_H / 2 + 40)
		return (1);
	return (0);
}

void	check_mouse_pos(t_data *data)
{
	int	y;
	int	x;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (!data->bigmap && !data->mouse && (mouse_pos(x, y, MNMAP_W / 2 + MNMAP_GAP, MNMAP_H / 2 + MNMAP_GAP)
		|| (x >= WIN_W - 90 && x <= WIN_W - 120 + 70 && y >= WIN_H - 150 && y <= WIN_H - 150 + 80)))
	{
		mlx_set_cursor(data->mlx, data->hnd_cursr);
	}
	else if (!data->mouse && data->bigmap && mouse_over_cross_icon(x, y))
	{
		mlx_set_cursor(data->mlx, data->hnd_cursr);
	}
	else
	{
		mlx_set_cursor(data->mlx, NULL);
	}
}

void	draw_shade_bg(t_data *data)
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
	// data->shade_bg->enabled = false;
}

void	mouse_event(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_data	*data;
	int		y;
	int		x;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& !data->bigmap && !data->mouse
		&& mouse_pos(x, y, MNMAP_W / 2 + MNMAP_GAP, MNMAP_H / 2 + MNMAP_GAP))
	{
		data->bigmap = true;
		data->map->mnmap_img->enabled = false;
		data->map->border_img->enabled = false;
		data->shade_bg = mlx_new_image(data->mlx, WIN_W, WIN_H);
		draw_shade_bg(data);
		data->bigmap_img = mlx_new_image(data->mlx, BIGMAP_W, BIGMAP_H);
		data->map->cross_img = mlx_texture_to_image(data->mlx, data->map->cross_txt);
		mlx_image_to_window(data->mlx, data->shade_bg, 0, 0);
		mlx_image_to_window(data->mlx, data->bigmap_img, WIN_W / 2 - BIGMAP_W / 2, WIN_H / 2 - BIGMAP_H / 2);
		mlx_image_to_window(data->mlx, data->map->cross_img, WIN_W / 2 - BIGMAP_W / 2, WIN_H / 2 - BIGMAP_H / 2);
		// data->bigmap_img->enabled = true;
		// data->map->cross_img->enabled = true;
		data->shade_bg->enabled = true;
		data->map->bigmap_y = data->plr->y;
		data->map->bigmap_x = data->plr->x;
		data->map->bigmap_py = BIGMAP_H / 2;
		data->map->bigmap_px = BIGMAP_W / 2;
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& data->bigmap && !data->mouse && mouse_over_cross_icon(x, y))
	{
		data->bigmap = false;
		mlx_delete_image(data->mlx, data->bigmap_img);
		mlx_delete_image(data->mlx, data->shade_bg);
		mlx_delete_image(data->mlx, data->map->cross_img);
		data->map->mnmap_img->enabled = true;
		data->map->border_img->enabled = true;
		data->bigmap_img->enabled = false;
		// data->map->cross_img->enabled = false;
		data->shade_bg->enabled = false;
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS && !data->bigmap && !data->mouse
		&& (x >= WIN_W - 90 && x <= WIN_W - 120 + 70 && y >= WIN_H - 150 && y <= WIN_H - 150 + 80))
	{
		if (!data->turning_on && data->light)
		{
			// data->idle_light_on_anm.frames[data->idle_light_on_anm.curr_frm]->enabled = false;
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
}
