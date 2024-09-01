/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/09/01 11:42:43 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// apply a rader around the player and check for wall collisions
static int	check_wall(t_data *data, int p_x, int p_y)
{
	int	x;
	int	y;
	int	deg;
	int	r;
	int	temp1;
	int	temp2;

	deg = 0;
	r = 7;
	while (deg < 360)
	{
		temp1 = r * sin(deg);
		temp2 = r * cos(deg);
		y = temp1 + p_y;
		x = temp2 + p_x;
		temp1 += MNMAP_H / 2;
		temp2 += MNMAP_W / 2;
		mlx_put_pixel(data->map->mnmap_img, temp2, temp1, get_rgba(255, 255, 0, 255));
		if (data->map->map[(int)(y / MNMAP_TILE_S)][(int)(x / MNMAP_TILE_S)] == '1')
			return (1);
		deg++;
	}
	return (0);
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
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->plr->rot_angl = remainder(data->plr->rot_angl - ROT_SPD, (2 * M_PI));
		if (data->plr->rot_angl < 0)
			data->plr->rot_angl += 2 * M_PI;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->plr->rot_angl = remainder(data->plr->rot_angl + ROT_SPD, (2 * M_PI));
	}
}

// check if player is moving (if a key is pressed)
bool	ab_is_moving(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) || mlx_is_key_down(data->mlx, MLX_KEY_W)
		|| mlx_is_key_down(data->mlx, MLX_KEY_S) || mlx_is_key_down(data->mlx, MLX_KEY_D)
		|| mlx_is_key_down(data->mlx, MLX_KEY_LEFT) || mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->is_moving = true;
	return (data->is_moving);
}

// draw rays casted on the minimap
void	draw_rays(t_data *data)
{
	int	i;

	i = -1;
	while (++i < N_RAYS)
	{
		ab_drawline(data, MNMAP_W / 2, MNMAP_H / 2, MNMAP_W / 2 + (int)(round(data->rays[i].x - data->plr->x)),
				MNMAP_H / 2 + (int)(round(data->rays[i].y - data->plr->y)), get_rgba(250, 188, 63, 255));
	}
}

// loop hook
void	ab_minimap(void *param)
{
	int	p_y;
	int	p_x;
	t_data	*data;

	data = (t_data *)param;
	p_y = -1;
	if (!ab_is_moving(data))
		return ;
	plr_move(data);
	raycasting(data);
	while (++p_y < MNMAP_H)
	{
		p_x = -1;
		while (++p_x < MNMAP_W)
		{
			if (check_pixel(data, p_y, p_x ) == 1)
				mlx_put_pixel(data->map->mnmap_img, p_x, p_y, get_rgba(32, 30, 67, 255));
			else if (check_pixel(data, p_y, p_x) == 0)
				mlx_put_pixel(data->map->mnmap_img, p_x, p_y, get_rgba(19, 75, 112, 255));
			else
				mlx_put_pixel(data->map->mnmap_img, p_x, p_y, get_rgba(80, 140, 155, 255));
		}
	}
	p_y = (MNMAP_H / 2) ;
	p_x = (MNMAP_W / 2) ;
	draw_rays(data);
	draw_circle(data, p_x, p_y, 3);
	check_wall(data, data->plr->x, data->plr->y);
	data->is_moving = false;
}
