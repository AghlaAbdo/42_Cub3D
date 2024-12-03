/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:01:17 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/03 12:51:21 by aaghla           ###   ########.fr       */
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



//	compare vertical & horizontal distance & choose the closer one
void	compare_vh_dstn(t_data *data, t_rays *ray, double h_dstn, double v_dstn)
{
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
}

// calculate the distance to the wall ans see which one is close (vert of horz)
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
	ray->door = false;
	compare_vh_dstn(data, ray, h_dstn, v_dstn);
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
static void renderworld(t_data *data)
{
	double		wall_h;
	double		pln_dstn;
	int			i;
	int			texture_x;
	int			texture_y;
	u_int8_t	*pixel;
	int			color;

	// Clear the window image before drawing
	ft_drw_fc(data);

	i = -1;
	while (++i < N_RAYS)  // Use N_RAYS instead of WIN_W
	{
		if (!data->rays[i].dstn)  // Safety check
			continue;

		data->rays[i].real_dstn = data->rays[i].dstn * 
			cos(adjust_angle(data->rays[i].angl - data->plr->rot_angl));
		pln_dstn = (WIN_W / 2) / tan(FOV / 2);
		wall_h = ((MNMAP_TILE_S / data->rays[i].real_dstn) * pln_dstn);

		// Safety check for texture selection
		ft_drctn_bsd_txtr(data, i);
		if (!data->applied_texture || !data->applied_texture->pixels)
			continue;

		// Bound checking for texture coordinates
		texture_x = get_texture_x(data, &data->rays[i], data->applied_texture->width);
		// Ensure texture_x is within bounds
		texture_x = texture_x < 0 ? 0 : texture_x;
		texture_x = texture_x >= data->applied_texture->width ? 
			data->applied_texture->width - 1 : texture_x;

		int start_y = (WIN_H / 2) - (wall_h / 2);
		int end_y = start_y + wall_h;

		// Bound checking for y coordinates
		start_y = start_y < 0 ? 0 : start_y;
		end_y = end_y >= WIN_H ? WIN_H - 1 : end_y;

		for (int y = start_y; y < end_y; y++)
		{
			int distance_from_top = y - WIN_H / 2 + wall_h / 2;
			texture_y = distance_from_top * ((float)MNMAP_TILE_S / wall_h);

			pixel = &data->applied_texture->pixels[
				(texture_y * data->applied_texture->width + texture_x) * 4];
			color = get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);

			if (i >= 0 && i < WIN_W && y >= 0 && y < WIN_H)  // Safety check
				mlx_put_pixel(data->win_img, i, y, color);
		}
	}
}

void	raycasting(t_data *data)
{
	int	i;

	i = -1;
	// ft_load_texture(data);
	ab_set_rayangl(data);
	while (++i < N_RAYS)
	{
		calc_horz(data, &data->rays[i], 0, 0);
		calc_vert(data, &data->rays[i], 0, 0);
		calc_dstn(data, &data->rays[i], 0, 0);
	}
	renderworld(data);
}