/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:50:44 by aaghla            #+#    #+#             */
/*   Updated: 2024/08/27 19:11:02 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

static int	check_wall(t_data *data, int p_x, int p_y)
{
	int	x;
	int	y;
	int	deg;
	int	r;
	int	temp1;
	int	temp2;

	// printf("p_y: %d | p_x: %d\n", p_y, p_x);
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
		// printf("x: %d | y: %d\n", x/ MNMAP_TILE_S, y/ MNMAP_TILE_S);
		mlx_put_pixel(data->map->mnmap_img, temp2, temp1, get_rgba(255, 255, 0, 255));
		if (data->map->map[(int)(y / MNMAP_TILE_S)][(int)(x / MNMAP_TILE_S)] == '1')
			return (1);
		deg++;
	}
	return (0);
}

// void	ab_keyhook(mlx_key_data_t keydata, void *param)
// {
// 	t_data	*data;
// 	int	x;
// 	int	y;

// 	data = (t_data *)param;
// 	x = cos(data->plr->rot_angl) * MOVE_SPD;
// 	y = sin(data->plr->rot_angl) * MOVE_SPD;
// 	// printf("%d\n", keydata.os_key);
// 	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 	{
// 		if (!check_wall(data, data->plr->x, data->plr->y + y))
// 			data->plr->y += y;
// 		if (!check_wall(data, data->plr->x + x, data->plr->y))
// 			data->plr->x += x;
// 	}
// 	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 	{
// 		if (!check_wall(data, data->plr->x, data->plr->y - y))
// 			data->plr->y -= y;
// 		if (!check_wall(data, data->plr->x - x, data->plr->y))
// 			data->plr->x -= x;
// 	}
// 	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 	{
// 		if (!check_wall(data, data->plr->x -MOVE_SPD, data->plr->y))
// 		data->plr->x -= MOVE_SPD;
// 	}
// 	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 	{
// 		if (!check_wall(data, data->plr->x + MOVE_SPD, data->plr->y))
// 			data->plr->x += MOVE_SPD;
// 	}
// 	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 		data->plr->rot_angl -= ROT_SPD;
// 	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
// 		data->plr->rot_angl += ROT_SPD;
// }

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
		// puts("here");
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
		if (data->plr->rot_angl - ROT_SPD < 0)
			data->plr->rot_angl = M_PI * 2;
		else
			data->plr->rot_angl -= ROT_SPD;
		// printf("plr rot: %f\n", data->plr->rot_angl);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		if (data->plr->rot_angl + ROT_SPD >= M_PI * 2)
			data->plr->rot_angl = 0;
		else
			data->plr->rot_angl += ROT_SPD;
		// printf("plr rot: %f\n", data->plr->rot_angl);
	}
}

void	ab_set_rayangl(t_data *data, int p_x, int p_y)
{
	int	i;
	double	ray_angl;

	i = -1;
	ray_angl = data->plr->rot_angl - (FOV / 2);
	while (++i < N_RAYS)
	{
		data->rays[i].angl = ray_angl;
		ray_angl += FOV / N_RAYS;
	}
	i = -1;
	while (++i < N_RAYS)
	{
		ab_drawline(data, p_x, p_y, p_x + (cos(data->rays[i].angl) * 90),
			p_y + (sin(data->rays[i].angl) * 90), get_rgba(110, 172, 218, 200));
	}
}

void	ab_minimap(void *param)
{
	int	p_y;
	int	p_x;
	t_data	*data;

	data = (t_data *)param;
	p_y = -1;
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
	draw_circle(data, p_x, p_y, 3);
	check_wall(data, data->plr->x, data->plr->y);
	ab_drawline(data, p_x, p_y, p_x + (cos(data->plr->rot_angl) * 70),
		p_y + (sin(data->plr->rot_angl) * 70), get_rgba(255, 0, 0, 255));
	plr_move(data);
	ab_set_rayangl(data, p_x, p_y);
}
