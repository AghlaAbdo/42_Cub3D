/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:27:50 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 23:03:12 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forword(t_data *data, double x, double y)
{
	if (!check_wall(data, data->plr->x, data->plr->y + y))
	{
		data->plr->y += y;
	}
	if (!check_wall(data, data->plr->x + x, data->plr->y))
	{
		data->plr->x += x;
	}
}

static void	move_backword(t_data *data, double x, double y)
{
	if (!check_wall(data, data->plr->x, data->plr->y - y))
	{
		data->plr->y -= y;
	}
	if (!check_wall(data, data->plr->x - x, data->plr->y))
	{
		data->plr->x -= x;
	}
}

static void	move_right(t_data *data, double x, double y)
{
	if (!check_wall(data, data->plr->x - y, data->plr->y))
	{
		data->plr->x -= y;
	}
	if (!check_wall(data, data->plr->x, data->plr->y + x))
	{
		data->plr->y += x;
	}
}

static void	move_left(t_data *data, double x, double y)
{
	if (!check_wall(data, data->plr->x + y, data->plr->y))
	{
		data->plr->x += y;
	}
	if (!check_wall(data, data->plr->x, data->plr->y - x))
	{
		data->plr->y -= x;
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plr->rot_angl = remainder(data->plr->rot_angl - ROT_SPD,
				(2 * M_PI));
		if (data->plr->rot_angl < 0)
			data->plr->rot_angl += 2 * M_PI;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->plr->rot_angl = remainder(data->plr->rot_angl + ROT_SPD,
				(2 * M_PI));
}
