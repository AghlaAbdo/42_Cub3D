/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:44:15 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/03 16:03:09 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// check the current pixel index content on the map
static int	check_pixel(t_data *data, int y, int x)
{
	int	i;
	int	j;

	i = (int)floor((data->map->y + y)) / 24 - (MNMAP_H / 24 / 2);
	j = (int)floor((data->map->x + x)) / 24 - (MNMAP_W / 24 / 2);
	y = (int)floor(data->map->y / 24);
	x = (int)floor(data->map->x / 24);
	if (i < 0 || j < 0 || i >= data->map->col || j >= data->map->row
		|| data->map->map[i][j] == ' ')
		return (-1);
	if (data->map->map[i][j] == '1')
		return (1);
	else if (data->map->map[i][j] == 'D' && (i != y || j != x))
		return (2);
	else
		return (0);
}

static void	render_pixel(t_data *data, int x, int y, int pixel)
{
	if (pixel == 1)
		mlx_put_pixel(data->map->mnmap_img, x, y,
			get_rgba(32, 30, 67, 255));
	else if (pixel == 0)
		mlx_put_pixel(data->map->mnmap_img, x, y,
			get_rgba(19, 75, 112, 255));
	else if (pixel == 2)
		mlx_put_pixel(data->map->mnmap_img, x, y,
			get_rgba(2, 131, 145, 255));
	else
		mlx_put_pixel(data->map->mnmap_img, x, y,
			get_rgba(80, 140, 155, 255));
}

void	draw_mnmap(t_data *data, int x, int y)
{
	int	dy;
	int	dx;

	y = -1;
	while (++y < MNMAP_H - 5)
	{
		dy = y - (MNMAP_H / 2);
		x = -1;
		while (++x < MNMAP_W - 5)
		{
			dx = x - (MNMAP_W / 2);
			if (dy * dy + dx * dx <= (MNMAP_W / 2 - 5) * (MNMAP_W / 2 - 5))
				render_pixel(data, x, y, check_pixel(data, y, x));
		}
	}
}

// draw rays casted on the minimap
void	draw_mnmap_rays(t_data *data)
{
	int	i;
	int	color;

	i = -1;
	while (++i < N_RAYS)
	{
		color = get_rgba(250, 188, 63, 255);
		if (data->rays[i].dstn * 0.12 > 65)
		{
			ab_drawline(data, MNMAP_W / 2, MNMAP_H / 2,
				round(MNMAP_W / 2 + cos(data->rays[i].angl) * 65.0),
				round(MNMAP_H / 2 + sin(data->rays[i].angl) * 65.0), color);
		}
		else
			ab_drawline(data, MNMAP_W / 2, MNMAP_H / 2, MNMAP_W / 2
				+ (int)(round(data->rays[i].x * 0.12 - data->plr->x * 0.12)),
				MNMAP_H / 2 + (int)(round(data->rays[i].y
						* 0.12 - data->plr->y * 0.12)), color);
	}
}
