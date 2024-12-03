/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:17:28 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/03 15:20:57 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mouse_over_mnmap(int ms_x, int ms_y, int x, int y)
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
	if (!data->bigmap && !data->mouse && (mouse_over_mnmap(x, y,
				MNMAP_W / 2 + MNMAP_GAP, MNMAP_H / 2 + MNMAP_GAP)
			|| (x >= WIN_W - 90 && x <= WIN_W - 120 + 70 && y >= WIN_H - 150
				&& y <= WIN_H - 150 + 80)))
		mlx_set_cursor(data->mlx, data->hnd_cursr);
	else if (!data->mouse && data->bigmap && mouse_over_cross_icon(x, y))
		mlx_set_cursor(data->mlx, data->hnd_cursr);
	else
		mlx_set_cursor(data->mlx, NULL);
}

void	mouse_event(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_data	*data;
	int		y;
	int		x;

	data = (t_data *)param;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& !data->bigmap && !data->mouse && mouse_over_mnmap(x, y,
			MNMAP_W / 2 + MNMAP_GAP, MNMAP_H / 2 + MNMAP_GAP))
	{
		show_big_map(data);
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& data->bigmap && !data->mouse && mouse_over_cross_icon(x, y))
	{
		hide_big_map(data);
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& !data->bigmap && !data->mouse && (x >= WIN_W - 90 && x <= WIN_W - 120
			+ 70 && y >= WIN_H - 150 && y <= WIN_H - 150 + 80))
		switch_light(data);
}
