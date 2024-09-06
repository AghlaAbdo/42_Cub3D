/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:35:03 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/06 09:39:05 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// apply a rader around the player and check for wall collisions
int	check_wall(t_data *data, int p_x, int p_y)
{
	int		x;
	int		y;
	double	deg;
	int		r;
	int		temp1;
	int		temp2;

	deg = 0;
	r = 7;
	while (deg < M_PI * 2)
	{
		temp1 = r * sin(deg);
		temp2 = r * cos(deg);
		y = temp1 + p_y;
		x = temp2 + p_x;
		temp1 += MNMAP_H / 2;
		temp2 += MNMAP_W / 2;
		mlx_put_pixel(data->map->mnmap_img, temp2, temp1, get_rgba(255, 255, 0, 255));
		if (data->map->map[(y / MNMAP_TILE_S)][(x / MNMAP_TILE_S)] == '1')
			return (1);
		deg += 0.5 * (M_PI / 180);
	}
	return (0);
}
// handle player movement
void	plr_move(t_data *data)
{
	double	x;
	double	y;

	x = cos(data->plr->rot_angl) * MOVE_SPD;
	y = sin(data->plr->rot_angl) * MOVE_SPD;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (!check_wall(data, data->plr->x, data->plr->y + y))
			data->plr->y += y;
		if (!check_wall(data, data->plr->x + x, data->plr->y))
			data->plr->x += x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (!check_wall(data, data->plr->x, data->plr->y - y))
			data->plr->y -= y;
		if (!check_wall(data, data->plr->x - x, data->plr->y))
			data->plr->x -= x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (!check_wall(data, data->plr->x - y, data->plr->y))
			data->plr->x -= y;
		if (!check_wall(data, data->plr->x, data->plr->y + x))
			data->plr->y += x;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (!check_wall(data, data->plr->x + y, data->plr->y))
			data->plr->x += y;
		if (!check_wall(data, data->plr->x, data->plr->y - x))
			data->plr->y -= x;
	}
	if (!data->mouse && mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plr->rot_angl = remainder(data->plr->rot_angl - ROT_SPD, (2 * M_PI));
		if (data->plr->rot_angl < 0)
			data->plr->rot_angl += 2 * M_PI;
	}
	if (!data->mouse && mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->plr->rot_angl = remainder(data->plr->rot_angl + ROT_SPD, (2 * M_PI));
	}
}

// Mouse movement
void	handle_mouse(t_data *data)
{
	int	curr_ms_x;
	int	curr_ms_y;

	
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(data->mlx, &curr_ms_x, &curr_ms_y);
	data->plr->rot_angl = remainder(data->plr->rot_angl + ((curr_ms_x - data->ms_x) * (M_PI / 180) * 0.08), (2 * M_PI));
	if (data->plr->rot_angl < 0)
		data->plr->rot_angl += 2 * M_PI;
	if (curr_ms_x <= 10 || curr_ms_x >= WIN_W - 10)
	{
		curr_ms_x = WIN_W / 2;
		mlx_set_mouse_pos(data->mlx, WIN_W / 2, WIN_H / 2);
	}
	data->ms_x = curr_ms_x;
}

// check if player is moving (if a key is pressed)
bool	ab_is_moving(t_data *data)
{
	if (data->mouse ||  mlx_is_key_down(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_D)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(data->mlx, MLX_KEY_L))
		data->is_moving = true;
	return (data->is_moving);
}
