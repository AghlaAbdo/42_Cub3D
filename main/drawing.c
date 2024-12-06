/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:56:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/05 12:43:17 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_drw_ln(mlx_image_t *img, int x1, int x2, int y)
{
	int	i;

	i = x1;
	while (i <= x2)
	{
		mlx_put_pixel(img, i, y, get_rgba(238, 238, 238, 255));
		i++;
	}
}

void	draw_circle(mlx_image_t *img, int h, int k, int r)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = r;
	d = 1 - r;
	while (x <= y)
	{
		ft_drw_ln(img, h - x, h + x, k + y);
		ft_drw_ln(img, h - x, h + x, k - y);
		ft_drw_ln(img, h - y, h + y, k + x);
		ft_drw_ln(img, h - y, h + y, k - x);
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

static void	plot(t_data *data, int x, int y, int color)
{
	mlx_put_pixel(data->map->mnmap_img, x, y, color);
}

void	ab_ft_drw_ln(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	if (x1 < x2)
		sx = 1;
	else
		sx = -1;
	if (y1 < y2)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		plot(data, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}
