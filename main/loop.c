/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/06 19:55:00 by aaghla           ###   ########.fr       */
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

void	move_map(t_data *data)
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

int	mouse_pos(int ms_x, int ms_y, int x, int y)
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

// void	check_mouse_pos(t_data *data)
// {
// 	int	y;
// 	int	x;

// 	mlx_get_mouse_pos(data->mlx, &x, &y);
// 	if (mouse_pos(x, y, MNMAP_W / 2 + MNMAP_GAP, MNMAP_H / 2 + MNMAP_GAP))
// 	{
// 		mlx_set_cursor_mode(data->mlx, MLX_CURSOR_HAND);
// 	}
// }

// loop hook
void	ft_looper(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->mouse && !data->big_mnmap)
		handle_mouse(data);
	// if (!data->mouse)
	// 	check_mouse_pos(data);
	if (data->big_mnmap)
		draw_big_mnmap(data);
	if (!ab_is_moving(data) || data->big_mnmap)
		return ;
	plr_move(data);
	raycasting(data);
	draw_mnmap(data);
	draw_mnmap_rays(data);
	draw_circle(data->map->mnmap_img, (MNMAP_W / 2), (MNMAP_H / 2), 3);
	check_wall(data, data->plr->x, data->plr->y);
	data->is_moving = false;
}
