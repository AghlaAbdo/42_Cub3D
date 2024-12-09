/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:01:17 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 18:31:04 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

void	raycasting(t_data *data)
{
	int	i;

	i = -1;
	ab_set_rayangl(data);
	while (++i < N_RAYS)
	{
		calc_horz(data, &data->rays[i], 0, 0);
		calc_vert(data, &data->rays[i], 0, 0);
		calc_dstn(data, &data->rays[i], 0, 0);
	}
	renderworld(data);
}
