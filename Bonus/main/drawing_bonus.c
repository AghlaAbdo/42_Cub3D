/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:56:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 18:15:08 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	ft_ln_nrm(t_data *data, int e2, int err, int color)
{
	while (1)
	{
		plot(data, data->ln_x1, data->ln_y1, color);
		if (data->ln_x1 == data->ln_x2 && data->ln_y1 == data->ln_y2)
			break ;
		e2 = err;
		if (e2 > -data->ln.dx)
		{
			err -= data->ln.dy;
			data->ln_x1 += data->ln.sx;
		}
		if (e2 < data->ln.dy)
		{
			err += data->ln.dx;
			data->ln_y1 += data->ln.sy;
		}
	}
}

void	ab_ft_drw_ln(t_data *data, int color)
{
	int	err;
	int	e2;

	e2 = 0;
	data->ln.dx = abs(data->ln_x2 - data->ln_x1);
	data->ln.dy = abs(data->ln_y2 - data->ln_y1);
	if (data->ln_x1 < data->ln_x2)
		data->ln.sx = 1;
	else
		data->ln.sx = -1;
	if (data->ln_y1 < data->ln_y2)
		data->ln.sy = 1;
	else
		data->ln.sy = -1;
	err = data->ln.dx - data->ln.dy;
	ft_ln_nrm(data, e2, err, color);
}
