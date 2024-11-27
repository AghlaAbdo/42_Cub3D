/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:01:17 by aaghla            #+#    #+#             */
/*   Updated: 2024/11/27 13:28:48 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

// set the ray angle and where the ray is facing for each ray
static void	ab_set_rayangl(t_data *data)
{
	int	i;
	double	ray_angl;

	i = -1;
	ray_angl = data->plr->rot_angl - (FOV / 2);
	while (++i < N_RAYS)
	{
		data->rays[i].angl = ray_angl;
		data->rays[i].angl = remainder(ray_angl, 2 * M_PI);
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
	}
	i = -1;
}

// check if the ray casted hit a wall
static int	is_wall(t_data *data, double x, double y, bool *found_wall, bool *door)
{
	int	i;
	int	j;

	i = (int)floor(y / MNMAP_TILE_S);
	j = (int)floor(x / MNMAP_TILE_S);
	if (i < 0 || i >= data->map->col || j < 0 || j >= data->map->row)
		return (-1);
	if (data->map->map[i][j] == '1' || data->map->map[i][j] == 'D')
	{
		*found_wall = true;
		if (data->map->map[i][j] == 'D')
			*door = true;
		else
			*door = false;
		return (1);
	}
	return (0);
}

// find horizontal wall touch
static void	calc_horz(t_data *data, t_rays *ray)
{
	double	yinter;
	double	xinter;
	double	ystep;
	double	xstep;
	int		up;
	
	up = 0;
	yinter = floor(data->plr->y / MNMAP_TILE_S) * MNMAP_TILE_S;
	if (!ray->is_up)
		yinter += MNMAP_TILE_S;
	xinter = data->plr->x + (yinter - data->plr->y) / tan(ray->angl);
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
	ray->found_h = false;
	while (1)
	{
		if (is_wall(data, xinter, yinter - up, &ray->found_h, &ray->door_h))
		{
			ray->h_x = xinter;
			ray->h_y = yinter;
			break ;
		}
		xinter += xstep;
		yinter += ystep;
	}
}

// find vertical wall touch
static void	calc_vert(t_data *data, t_rays *ray)
{
	double	yinter;
	double	xinter;
	double	ystep;
	double	xstep;
	int		left;

	left = 0;
	xinter = floor(data->plr->x / MNMAP_TILE_S) * MNMAP_TILE_S;
	if (!ray->is_left)
		xinter += MNMAP_TILE_S;
	yinter = data->plr->y + (xinter - data->plr->x) * tan(ray->angl);
	xstep = MNMAP_TILE_S;
	if (ray->is_left)
	{
		xstep *= -1;
		left = 1;
	}
	ystep = MNMAP_TILE_S * tan(ray->angl);
	if (ray->is_up && ystep > 0)
		ystep *= -1;
	if (!ray->is_up && ystep < 0)
		ystep *= -1;
	ray->found_v = false;
	while (1)
	{
		if (is_wall(data, xinter - left, yinter, &ray->found_v, &ray->door_v))
		{
			ray->v_x = xinter;
			ray->v_y = yinter;
			break ;
		}
		xinter += xstep;
		yinter += ystep;
	}
}

// calculate the distance to the wall ans see which one is close (vert of horz)
void	calc_dstn(t_data *data, t_rays *ray)
{
	double	h_dstn;
	double	v_dstn;
	
	if (ray->found_h)
		h_dstn = sqrt((ray->h_x - data->plr->x) * (ray->h_x - data->plr->x)
			+ (ray->h_y - data->plr->y) * (ray->h_y - data->plr->y));
	else
		h_dstn = INT_MAX;
	if (ray->found_v)
		v_dstn = sqrt((ray->v_x - data->plr->x) * (ray->v_x - data->plr->x)
			+ (ray->v_y - data->plr->y) * (ray->v_y - data->plr->y));
	else
		v_dstn = INT_MAX;
	ray->door = false;
	if (h_dstn < v_dstn)
	{
		ray->dstn = h_dstn;
		ray->x = ray->h_x;
		ray->y = ray->h_y;
		ray->orn = 'h';
		if (ray->door_h)
			ray->door = true;
	}
	else
	{
		ray->dstn = v_dstn;
		ray->x = ray->v_x;
		ray->y = ray->v_y;
		ray->orn = 'v';
		if (ray->door_v)
			ray->door = true;
	}
	// if (data->map->map[(int)floor(ray->y / MNMAP_TILE_S)][(int)floor(ray->x / MNMAP_TILE_S)] == 'D')
	// {
	// 	// printf("is D\n");
	// 	ray->orn = 'D';
	// }
}

double	adjust_angle(double angle)
{
	double	res_angle;

	res_angle = remainder(angle, M_PI * 2);
	if (res_angle < 0)
		res_angle += M_PI * 2;
	return (res_angle);
}

// calculate the wall height and render the 3D world
static void	renderworld(t_data *data)
{
	double	wall_h;
	double	pln_dstn;
	double	ray_dstn;
	int		i;
	int		color;

	i = -1;
	while (++i < N_RAYS)
	{
		data->rays[i].real_dstn = data->rays[i].dstn * cos(adjust_angle(data->rays[i].angl - data->plr->rot_angl));
		pln_dstn = (WIN_W / 2) / tan(FOV / 2);
		wall_h = ((MNMAP_TILE_S / data->rays[i].real_dstn) * pln_dstn);
		// printf("color res: %f\n", 255 - data->rays[i].real_dstn * 255 / 500);
		if (data->rays[i].orn == 'h')
			color = get_rgba(13, 124, 102, 255 - data->rays[i].real_dstn * 255 / 500);
		else
			color = get_rgba(65, 179, 162,  255 - data->rays[i].real_dstn * 255 / 500);
		draw_ray(data, i, round((WIN_H / 2 - (wall_h / 2))), 1, round(wall_h));
	}
}

void	raycasting(t_data *data)
{
	int	i;

	i = -1;
	ab_set_rayangl(data);
	while (++i < N_RAYS)
	{
		calc_horz(data, &data->rays[i]);
		calc_vert(data, &data->rays[i]);
		calc_dstn(data, &data->rays[i]);
	}
	renderworld(data);
}