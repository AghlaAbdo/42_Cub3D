/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:44:15 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/06 09:53:04 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


// check the current pixel index content on the map
static int	check_pixel(t_data *data, int y, int x)
{
	int	i;
	int	j;

	i = (int)round((data->plr->y + y)) / MNMAP_TILE_S - (MNMAP_H / MNMAP_TILE_S / 2);
	j = (int)round((data->plr->x + x)) / MNMAP_TILE_S - (MNMAP_W / MNMAP_TILE_S / 2);
	if (i < 0 || j < 0 || i >= data->map->col || j >= data->map->row)
		return (-1);
	if (data->map->map[i][j] == '1')
		return (1);
	else if (data->map->map[i][j] == '0' || data->map->map[i][j] == 'N'
		|| data->map->map[i][j] == 'S' || data->map->map[i][j] == 'E'
		|| data->map->map[i][j] == 'W')
		return (0);
	return (-1);
}

void	draw_mnmap(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < MNMAP_H)
	{
		x = -1;
		while (++x < MNMAP_W)
		{
			if (check_pixel(data, y, x ) == 1)
				mlx_put_pixel(data->map->mnmap_img, x, y, get_rgba(32, 30, 67, 255));
			else if (check_pixel(data, y, x) == 0)
				mlx_put_pixel(data->map->mnmap_img, x, y, get_rgba(19, 75, 112, 255));
			else
				mlx_put_pixel(data->map->mnmap_img, x, y, get_rgba(80, 140, 155, 255));
		}
	}
}

// draw rays casted on the minimap
void	draw_mnmap_rays(t_data *data)
{
	int	i;
	int	j;
	int	color;

	i = -1;
	while (++i < MNMAP_H)
	{
		j = -1;
		while (++j < MNMAP_W)
		{
			mlx_put_pixel(data->ray_img, j, i, get_rgba(0, 0, 0, 0));
		}
	}
	i = -1;
	while (++i < N_RAYS)
	{
		color = get_rgba(250, 188, 63, 200);
		if (data->rays[i].dstn > 65)
		{
			ab_drawline(data, MNMAP_W / 2, MNMAP_H / 2, round(MNMAP_W / 2 + cos(data->rays[i].angl) * 65.0),
				round(MNMAP_H / 2 + sin(data->rays[i].angl) * 65.0), color);
		}
		else
			ab_drawline(data, MNMAP_W / 2, MNMAP_H / 2, MNMAP_W / 2 + (int)(round(data->rays[i].x - data->plr->x)),
				MNMAP_H / 2 + (int)(round(data->rays[i].y - data->plr->y)), color);
	}
}
