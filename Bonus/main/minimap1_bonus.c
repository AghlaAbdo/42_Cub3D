/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:09:35 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 18:14:39 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
