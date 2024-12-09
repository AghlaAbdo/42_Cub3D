/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:44:15 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 18:14:43 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_ln_init(t_data *data, int flg, int i)
{
	if (flg)
	{
		data->ln_x1 = MNMAP_W / 2;
		data->ln_y1 = MNMAP_H / 2;
		data->ln_x2 = round(MNMAP_W / 2 + cos(data->rays[i].angl) * 65.0);
		data->ln_y2 = round(MNMAP_H / 2 + sin(data->rays[i].angl) * 65.0);
	}
	else
	{
		data->ln_x1 = MNMAP_W / 2;
		data->ln_y1 = MNMAP_H / 2;
		data->ln_x2 = MNMAP_W / 2 + (int)(round(data->rays[i].x
					* 0.12 - data->plr->x * 0.12));
		data->ln_y2 = MNMAP_H / 2 + (int)(round(data->rays[i].y
					* 0.12 - data->plr->y * 0.12));
	}
}

// draw rays casted on the minimap
void	draw_mnmap_rays(t_data *data)
{
	int	i;
	int	color;

	i = -1;
	while (++i < N_RAYS)
	{
		color = get_rgba(250, 188, 63, 255);
		if (data->rays[i].dstn * 0.12 > 65)
		{
			ft_ln_init(data, 1, i);
			ab_ft_drw_ln(data, color);
		}
		else
		{
			ft_ln_init(data, 0, i);
			ab_ft_drw_ln(data, color);
		}
	}
}
