/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:35:03 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/03 16:07:54 by aaghla           ###   ########.fr       */
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
	r = 7;
	while (deg < M_PI * 2)
	{
		y = r * sin(deg);
		x = r * cos(deg);
		mlx_put_pixel(data->map->mnmap_img, x + MNMAP_W / 2, y + MNMAP_H / 2,
			get_rgba(255, 255, 0, 255));
		if (data->map->map[(y + p_y) / 24][(x + p_x) / 24] == '1')
			return (1);
		deg += 0.5 * (M_PI / 180);
	}
	return (0);
}

// Mouse movement
void	handle_mouse(t_data *data)
{
	int	curr_ms_x;
	int	curr_ms_y;

	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(data->mlx, &curr_ms_x, &curr_ms_y);
	data->plr->rot_angl = remainder(data->plr->rot_angl
			+ ((curr_ms_x - data->ms_x) * (M_PI / 180) * 0.05), (2 * M_PI));
	if (data->plr->rot_angl < 0)
		data->plr->rot_angl += 2 * M_PI;
	if (curr_ms_x <= 10 || curr_ms_x >= WIN_W - 10
		|| curr_ms_y <= 10 || curr_ms_y >= WIN_H - 10)
	{
		curr_ms_x = WIN_W / 2;
		mlx_set_mouse_pos(data->mlx, WIN_W / 2, WIN_H / 2);
	}
	data->ms_x = curr_ms_x;
}

// check if player is moving (if a key is pressed)
bool	is_plr_moving(t_data *data)
{
	if (data->mouse)
		data->rendering = true;
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
