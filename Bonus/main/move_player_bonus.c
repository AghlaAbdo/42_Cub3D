/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:27:50 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 18:14:32 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	move_forword(t_data *data, double x, double y)
{
	if (!check_wall(data, data->map->x, data->map->y + y * 0.12))
	{
		data->map->y += y * 0.12;
		data->plr->y += y;
	}
	if (!check_wall(data, data->map->x + x * 0.12, data->map->y))
	{
		data->map->x += x * 0.12;
		data->plr->x += x;
	}
}

static void	move_backword(t_data *data, double x, double y)
{
	if (!check_wall(data, data->map->x, data->map->y - y * 0.12))
	{
		data->map->y -= y * 0.12;
		data->plr->y -= y;
	}
	if (!check_wall(data, data->map->x - x * 0.12, data->map->y))
	{
		data->map->x -= x * 0.12;
		data->plr->x -= x;
	}
}

static void	move_right(t_data *data, double x, double y)
{
	if (!check_wall(data, data->map->x - y * 0.12, data->map->y))
	{
		data->plr->x -= y;
		data->map->x -= y * 0.12;
	}
	if (!check_wall(data, data->map->x, data->map->y + x * 0.12))
	{
		data->plr->y += x;
		data->map->y += x * 0.12;
	}
}

static void	move_left(t_data *data, double x, double y)
{
	if (!check_wall(data, data->map->x + y * 0.12, data->map->y))
	{
		data->map->x += y * 0.12;
		data->plr->x += y;
	}
	if (!check_wall(data, data->map->x, data->map->y - x * 0.12))
	{
		data->plr->y -= x;
		data->map->y -= x * 0.12;
	}
}

// handle player movement
void	move_plr(t_data *data)
{
	double	x;
	double	y;

	x = cos(data->plr->rot_angl) * MOVE_SPD;
	y = sin(data->plr->rot_angl) * MOVE_SPD;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forword(data, x, y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backword(data, x, y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data, x, y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data, x, y);
	if (!data->mouse && mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plr->rot_angl = remainder(data->plr->rot_angl - ROT_SPD,
				(2 * M_PI));
		if (data->plr->rot_angl < 0)
			data->plr->rot_angl += 2 * M_PI;
	}
	if (!data->mouse && mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->plr->rot_angl = remainder(data->plr->rot_angl + ROT_SPD,
				(2 * M_PI));
}
