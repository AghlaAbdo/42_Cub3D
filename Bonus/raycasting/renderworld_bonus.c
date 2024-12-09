/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderworld_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:26:08 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/08 16:06:42 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

static void	clte_wll_prms(t_data *data, int i, double *wall_h, double *pln_dstn)
{
	data->rays[i].real_dstn = data->rays[i].dstn
		* cos(adjust_angle(data->rays[i].angl - data->plr->rot_angl));
	*pln_dstn = (WIN_W / 2) / tan(FOV / 2);
	*wall_h = ((MNMAP_TILE_S / data->rays[i].real_dstn) * (*pln_dstn));
}

static int	get_texture_x_clamped(t_data *data, int i)
{
	int	texture_x;

	texture_x = get_texture_x(data, &data->rays[i],
			data->applied_texture->width);
	if (texture_x < 0)
		texture_x = 0;
	if (texture_x >= (int)data->applied_texture->width)
		texture_x = data->applied_texture->width - 1;
	return (texture_x);
}

static void	calculate_wall_boundaries(t_data *data, double wall_h)
{
	data->rw_strt_y = (WIN_H / 2) - (wall_h / 2);
	data->rw_end_y = data->rw_strt_y + wall_h;
	if (data->rw_strt_y < 0)
		data->rw_strt_y = 0;
	if (data->rw_end_y >= WIN_H)
		data->rw_end_y = WIN_H - 1;
}

static void	render_column(t_data *data, int i, int texture_x, double wall_h)
{
	int	texture_y;

	data->rw_y = data->rw_strt_y;
	while (data->rw_y < data->rw_end_y)
	{
		data->rw_dst_frm_tp = data->rw_y - WIN_H / 2 + wall_h / 2;
		texture_y = data->rw_dst_frm_tp * ((float)MNMAP_TILE_S / wall_h);
		data->rw_pxl = &data->applied_texture->pixels[
			(texture_y * data->applied_texture->width + texture_x) * 4];
		data->rw_clr = get_rgba(data->rw_pxl[0], data->rw_pxl[1],
				data->rw_pxl[2], data->rw_alp);
		data->rw_y++;
		if (i >= 0 && i <= WIN_W && data->rw_y >= 0 && data->rw_y <= WIN_H)
			mlx_put_pixel(data->win_img, i, data->rw_y, data->rw_clr);
	}
}

void	renderworld(t_data *data)
{
	double	wall_h;
	double	pln_dstn;
	int		i;
	int		texture_x;

	ft_drw_fc(data);
	i = -1;
	while (++i < N_RAYS)
	{
		clte_wll_prms(data, i, &wall_h, &pln_dstn);
		ft_drctn_bsd_txtr(data, i);
		calculate_wall_boundaries(data, wall_h);
		set_alpha(data, data->rays[i], &data->rw_alp);
		texture_x = get_texture_x_clamped(data, i);
		render_column(data, i, texture_x, wall_h);
	}
}
