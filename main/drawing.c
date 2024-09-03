/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:56:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/03 17:36:21 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	drawLine(t_data *data, int x1, int x2, int y) {
	for (int i = x1; i <= x2; i++) {
		mlx_put_pixel(data->map->mnmap_img, i, y, get_rgba(238, 238, 238, 255));
	}
}

void	draw_circle(t_data *data, int h, int k, int r)
{
	int x = 0;
	int y = r;
	int d = 1 - r;

	while (x <= y) {
		drawLine(data, h - x, h + x, k + y);
		drawLine(data, h - x, h + x, k - y);
		drawLine(data, h - y, h + y, k + x);
		drawLine(data, h - y, h + y, k - x);

		if (d < 0) {
			d += 2 * x + 3;
		} else {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

static void	plot(t_data *data, int x, int y, int color) {
   mlx_put_pixel(data->ray_img, x, y, color);
}

void	ab_drawline(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	if (x2 >= MNMAP_W || x2 < 0)
	{
		// printf("x > mnmap_w\n");
		x2 = MNMAP_W / 2;
		y2 = MNMAP_H / 2;
	}
	if (y2 >= MNMAP_H || y2 < 0)
	{
		// printf("y > mnmap_h\n");
		x2 = MNMAP_W / 2;
		y2 = MNMAP_H / 2;
	}

	
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = dx - dy;
	int e2;
	while (1) {
		plot(data, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
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

// draw a single ray on the window
void	draw_ray(t_data *data, int x, int y, int w, int h)
{
	int	i;
	int	j;
	int	x_start;
	int	color;
	int	alpha;
	int	floor_alpha;

	alpha = 255;
	floor_alpha = 255;
	if (!data->light)
	{
		alpha = 255 - data->rays[x].real_dstn * 255 / 700;
		if (alpha < 0)
			alpha = 0;
		else if (alpha > 255)
			alpha = 255;
	}
	if (data->rays[x].orn == 'h')
		color = get_rgba(120, 171, 168, alpha);
	else
		color = get_rgba(124, 175, 171,  alpha);
	i = 0;
	if (y < 0)
	{
		while (i < WIN_H)
			mlx_put_pixel(data->win_img, x, i++, color);
		return ;
	}
	while (i < WIN_H && i < y)
		mlx_put_pixel(data->win_img, x, i++, get_rgba(23, 155, 174, 255));
	while (i < WIN_H && i < h + y)
		mlx_put_pixel(data->win_img, x, i++, color);
	while (i < WIN_H)
	{
		if (!data->light)
			floor_alpha = (i - WIN_H / 3) * 255 / (WIN_H - (WIN_H / 3));
		// printf("floor alpha: %d\n", floor_alpha);
		// if (floor_alpha < 0)
		// 	floor_alpha = 0;
		// else if (floor_alpha > 255)
		// 	floor_alpha = 255;
		mlx_put_pixel(data->win_img, x, i++, get_rgba(34, 123, 148,  floor_alpha));
	}
}
