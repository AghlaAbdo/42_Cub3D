/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 08:46:55 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 23:05:17 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	ab_set_rayangl(t_data *data)
{
	int		i;
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

//	compare vertical & horizontal distance & choose the closer one
void	cmp_vh_dst(t_data *data, t_rays *ray, double h_dstn, double v_dstn)
{
	(void)data;
	if (h_dstn < v_dstn)
	{
		ray->dstn = h_dstn;
		ray->x = ray->h_x;
		ray->y = ray->h_y;
		ray->orn = 'h';
	}
	else
	{
		ray->dstn = v_dstn;
		ray->x = ray->v_x;
		ray->y = ray->v_y;
		ray->orn = 'v';
	}
}

void	calc_dstn(t_data *data, t_rays *ray, double h_dstn, double v_dstn)
{
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
	cmp_vh_dst(data, ray, h_dstn, v_dstn);
}

double	adjust_angle(double angle)
{
	double	res_angle;

	res_angle = remainder(angle, M_PI * 2);
	if (res_angle < 0)
		res_angle += M_PI * 2;
	return (res_angle);
}
