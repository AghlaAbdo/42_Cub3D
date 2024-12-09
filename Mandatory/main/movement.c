/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:35:03 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 23:06:24 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// apply a rader around the player and check for wall collisions
int	check_wall(t_data *data, int p_x, int p_y)
{
	double	deg;
	int		x;
	int		y;
	int		r;

	deg = 0;
	r = 30;
	while (deg < M_PI * 2)
	{
		y = r * sin(deg);
		x = r * cos(deg);
		if (data->map->map[(y + p_y) / MNMAP_TILE_S]
			[(x + p_x) / MNMAP_TILE_S] == '1')
			return (1);
		deg += 0.5 * (M_PI / 180);
	}
	return (0);
}

// check if player is moving (if a key is pressed)
bool	is_plr_moving(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx,
			MLX_KEY_W) || mlx_is_key_down(data->mlx, MLX_KEY_S)
		|| mlx_is_key_down(data->mlx, MLX_KEY_D) || mlx_is_key_down(data->mlx,
			MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_L))
	{
		data->rendering = true;
		data->is_moving = true;
	}
	if (data->rendering || data->is_moving)
		return (true);
	return (false);
}
