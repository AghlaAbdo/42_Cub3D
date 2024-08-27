/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:56:36 by aaghla            #+#    #+#             */
/*   Updated: 2024/08/27 17:40:43 by aaghla           ###   ########.fr       */
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
   mlx_put_pixel(data->map->mnmap_img, x, y, color);
}

void	ab_drawline(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = x1 < x2 ? 1 : -1;
	int sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	while (1) {
		plot(data, x1, y1, color);
		if (x1 == x2 && y1 == y2) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
	}
}
