/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:17:45 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/07 19:17:59 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	big_mnmap_pixel(t_data *data, int y, int x)
{
	int	i;
	int	j;

	i = (int)round((data->map->y + y)) / MNMAP_TILE_S - (BIG_MNMAP_H / MNMAP_TILE_S / 2);
	j = (int)round((data->map->x + x)) / MNMAP_TILE_S - (BIG_MNMAP_W / MNMAP_TILE_S / 2);
	if (i < 0 || j < 0 || i >= data->map->col || j >= data->map->row || data->map->map[i][j] == ' ')
		return (-1);
	if (data->map->map[i][j] == '1')
		return (1);
	else
		return (0);
}

static void	move_map(t_data *data)
{
	if (data->map->x / MNMAP_TILE_S >= 0 && mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->map->x -= MOVE_SPD * 5;
		data->map->p_x += MOVE_SPD * 5;
	}
	if (data->map->x / MNMAP_TILE_S < data->map->row && mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->map->x += MOVE_SPD * 5;
		data->map->p_x -= MOVE_SPD * 5;
	}
	if (data->map->y / MNMAP_TILE_S >= 0 && mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->map->y -= MOVE_SPD * 5;
		data->map->p_y += MOVE_SPD * 5;
	}
	if (data->map->y / MNMAP_TILE_S < data->map->col && mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->map->y += MOVE_SPD * 5;
		data->map->p_y -= MOVE_SPD * 5;
	}
}

void	draw_big_mnmap(t_data *data)
{
	int	y;
	int	x;
	int	pixel;

	y = -1;
	while (++y < BIG_MNMAP_H)
	{
		x = -1;
		while (++x < BIG_MNMAP_W)
		{
			pixel = big_mnmap_pixel(data, y, x );
			if (pixel == 1)
				mlx_put_pixel(data->big_mnmp_img, x, y, get_rgba(32, 30, 67, 255));
			else if (pixel == 0 || pixel == 2)
				mlx_put_pixel(data->big_mnmp_img, x, y, get_rgba(19, 75, 112, 255));
			else
				mlx_put_pixel(data->big_mnmp_img, x, y, get_rgba(80, 140, 155, 255));
		}
	}
	if  (data->map->p_x > 3 && data->map->p_y > 3 && data->map->p_x < BIG_MNMAP_W - 3 && data->map->p_y < BIG_MNMAP_H -3)
		draw_circle(data->big_mnmp_img, data->map->p_x, data->map->p_y, 4);
	move_map(data);
}