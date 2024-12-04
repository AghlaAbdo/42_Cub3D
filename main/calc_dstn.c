/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dstn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:50:23 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/04 18:50:03 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check if the ray casted hit a wall
static int	is_wall(t_data *data, double x, double y,
	bool *found_wall, bool *door)
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

//	calc horizontal x y steps
void	calc_h_xystep(t_data *data, t_rays *ray, double *ystep, double *xstep)
{
	*ystep = MNMAP_TILE_S;
	if (ray->is_up)
	{
		*ystep *= -1;
	}
	*xstep = MNMAP_TILE_S / tan(ray->angl);
	if (ray->is_left && *xstep > 0)
		*xstep *= -1;
	if (!ray->is_left && *xstep < 0)
		*xstep *= -1;
}

// find horizontal wall touch
void	calc_horz(t_data *data, t_rays *ray, double xstep, int up)
{
	double	yinter;
	double	xinter;
	double	ystep;

	yinter = floor(data->plr->y / MNMAP_TILE_S) * MNMAP_TILE_S;
	if (!ray->is_up)
		yinter += MNMAP_TILE_S;
	xinter = data->plr->x + (yinter - data->plr->y) / tan(ray->angl);
	calc_h_xystep(data, ray, &ystep, &xstep);
	if (ray->is_up)
		up = 1;
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

//	calc vertical x y steps
void	calc_v_xystep(t_data *data, t_rays *ray, double *ystep, double *xstep)
{
	*xstep = MNMAP_TILE_S;
	if (ray->is_left)
	{
		*xstep *= -1;
	}
	*ystep = MNMAP_TILE_S * tan(ray->angl);
	if (ray->is_up && *ystep > 0)
		*ystep *= -1;
	if (!ray->is_up && *ystep < 0)
		*ystep *= -1;
}

// find vertical wall touch
void	calc_vert(t_data *data, t_rays *ray, double xstep, int left)
{
	double	yinter;
	double	xinter;
	double	ystep;

	xinter = floor(data->plr->x / MNMAP_TILE_S) * MNMAP_TILE_S;
	if (!ray->is_left)
		xinter += MNMAP_TILE_S;
	yinter = data->plr->y + (xinter - data->plr->x) * tan(ray->angl);
	calc_v_xystep(data, ray, &ystep, &xstep);
	if (ray->is_left)
		left = 1;
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
