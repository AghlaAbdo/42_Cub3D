/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:17:45 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 19:29:02 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	bigmap_pixel(t_data *data, int y, int x)
// {
// 	int	i;
// 	int	j;

// 	i = (int)floor((data->map->bigmap_y + y)) / 24 - (BIGMAP_H / 24 / 2);
// 	j = (int)floor((data->map->bigmap_x + x)) / 24 - (BIGMAP_W / 24 / 2);
// 	y = (int)floor(data->map->y / 24);
// 	x = (int)floor(data->map->x / 24);
// 	if (i < 0 || j < 0 || i >= data->map->col || j >= data->map->row
// 		|| data->map->map[i][j] == ' ')
// 		return (-1);
// 	if (data->map->map[i][j] == '1')
// 		return (1);
// 	else if (data->map->map[i][j] == 'D' && (i != y || j != x))
// 		return (2);
// 	else
// 		return (0);
// }

// static void	move_map(t_data *data)
// {
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)
// 		&& data->map->bigmap_x / 24 >= 0)
// 	{
// 		data->map->bigmap_x -= MOVE_SPD;
// 		data->map->bigmap_px += MOVE_SPD;
// 	}
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
// 		&& data->map->bigmap_x / 24 < data->map->row)
// 	{
// 		data->map->bigmap_x += MOVE_SPD;
// 		data->map->bigmap_px -= MOVE_SPD;
// 	}
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_UP)
// 		&& data->map->bigmap_y / 24 >= 0)
// 	{
// 		data->map->bigmap_y -= MOVE_SPD;
// 		data->map->bigmap_py += MOVE_SPD;
// 	}
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN)
// 		&& data->map->bigmap_y / 24 < data->map->col)
// 	{
// 		data->map->bigmap_y += MOVE_SPD;
// 		data->map->bigmap_py -= MOVE_SPD;
// 	}
// }

// static	void	render_pixel(t_data *data, int x, int y, int pixel)
// {
// 	if (pixel == 1)
// 		mlx_put_pixel(data->bigmap_img, x, y, get_rgba(32, 30, 67, 255));
// 	else if (pixel == 0)
// 		mlx_put_pixel(data->bigmap_img, x, y, get_rgba(19, 75, 112, 255));
// 	else if (pixel == 2)
// 		mlx_put_pixel(data->bigmap_img, x, y, get_rgba(2, 131, 145, 255));
// 	else
// 		mlx_put_pixel(data->bigmap_img, x, y, get_rgba(80, 140, 155, 255));
// }

// void	draw_bigmap(t_data *data)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (++y < BIGMAP_H)
// 	{
// 		x = -1;
// 		while (++x < BIGMAP_W)
// 			render_pixel(data, x, y, bigmap_pixel(data, y, x));
// 	}
// 	if (data->map->bigmap_px > 3 && data->map->bigmap_py > 3
// 		&& data->map->bigmap_px < BIGMAP_W - 3
// 		&& data->map->bigmap_py < BIGMAP_H - 3)
// 		draw_circle(data->bigmap_img, data->map->bigmap_px,
// 			data->map->bigmap_py, 4);
// 	move_map(data);
// }
