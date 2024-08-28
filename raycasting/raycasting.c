/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:01:17 by aaghla            #+#    #+#             */
/*   Updated: 2024/08/28 18:45:15 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	ab_set_rayangl(t_data *data, int p_x, int p_y)
{
	int	i;
	double	ray_angl;

	i = -1;
	ray_angl = data->plr->rot_angl - (FOV / 2);
	// printf("plr angle: %f  | (FOV / 2): %f\n", data->plr->rot_angl, FOV / 2);
	while (++i < N_RAYS)
	{
		data->rays[i].angl = ray_angl;
		data->rays[i].angl = fmod(ray_angl, 2 * M_PI);
		if (data->rays[i].angl < 0)
			data->rays[i].angl += 2 * M_PI;
		if (data->rays[i].angl > 0 && data->rays[i].angl < M_PI)
			data->rays[i].is_up = false;
		else
			data->rays[i].is_up = true;
		if (data->rays[i].angl > M_PI / 2 && data->rays[i].angl < M_PI * 1.5)
			data->rays[i].is_left = true;
		else
			data->rays[i].is_left = false;
		ray_angl += FOV / N_RAYS;
		// ray_angl = fmod(ray_angl + (FOV / N_RAYS), (2 * M_PI));
		// if (ray_angl < 0)
		// 	ray_angl = 2 * M_PI;
	}
	i = -1;
	// (void)p_y;
	// (void)p_x;
		// printf("ray[%d].angle: %f\n", 0, data->rays[0].angl);
	while (++i < N_RAYS)
	{
		ab_drawline(data, p_x, p_y, p_x + (cos(data->rays[i].angl) * 90),
			p_y + (sin(data->rays[i].angl) * 90), get_rgba(110, 172, 218, 200));
	}
}
int	is_wall(t_data *data, double x, double y)
{
	int	i;
	int	j;
	// int	deg;
	// int	r;
	// int	temp1;
	// int	temp2;

	// printf("p_y: %d | p_x: %d\n", p_y, p_x);
	// deg = 0;
	// r = 7;
	// while (deg < 360)
	// {
	// 	temp1 = r * sin(deg);
	// 	temp2 = r * cos(deg);
	// 	y = temp1 + p_y;
	// 	x = temp2 + p_x;
	// 	temp1 += MNMAP_H / 2;
	// 	temp2 += MNMAP_W / 2;
	i = y / MNMAP_TILE_S;
	j = x / MNMAP_TILE_S;
	if (i < 0 || i > data->map->col || j < 0 || j > data->map->row)
	{
	printf("i: %d | j: %d\n", i, j);
		return (1);
	}
		// printf("x: %d | y: %d\n", x/ MNMAP_TILE_S, y/ MNMAP_TILE_S);
		// mlx_put_pixel(data->map->mnmap_img, temp2, temp1, get_rgba(255, 255, 0, 255));
		if (data->map->map[i][j] == '1')
			return (1);
		// deg++;
	// }
	return (0);
}

void	calc_hori(t_data *data, t_rays *ray)
{
	// int	i;
	double	yinter;
	double	xinter;
	double	ystep;
	double	xstep;
	int	up;
	
	up = 0;
	yinter = floor(data->plr->y / MNMAP_TILE_S) * MNMAP_TILE_S;
	if (!ray->is_up)
		yinter += MNMAP_TILE_S;
	printf("yinter: %f | plr y: %f  | plr x: %f\n", yinter, data->plr->y, data->plr->x);
	// printf("tan(6.283185): %f\n", tan(6.283185));
	// xinter = data->plr->x + ((yinter - data->plr->y) / tan(ray->angl));
	xinter = yinter;
	ystep = MNMAP_TILE_S;
	if (ray->is_up)
	{
		ystep *= -1;
		up = 1;
	}
	xstep = MNMAP_TILE_S / tan(ray->angl);
	if (ray->is_left && xstep > 0)
		xstep *= -1;
	if (!ray->is_left && xstep < 0)
		xstep *= -1;
		printf("bef while xinter: %f  | yinter: %f  | ray angle: %f\n", xinter, yinter, ray->angl);
	while (1)
	{
		printf("in while xinter: %f  | yinter: %f  | ray angle: %f\n", xinter, yinter, ray->angl);
		if (is_wall(data, xinter, yinter - up))
		{
		printf("here?\n");
			ray->x = xinter;
			ray->y = yinter;
			break ;
		}
		xinter += xstep;
		yinter += ystep;
	ab_drawline(data, data->plr->x, data->plr->y, ray->x,
			ray->y, get_rgba(255, 0, 0, 255));
	}
}

void	raycasting(t_data *data)
{
	ab_set_rayangl(data, MNMAP_W / 2, MNMAP_H / 2);
	// for (int i = 0; i < N_RAYS; i++)
		// calc_hori(data, &data->rays[0]);
}