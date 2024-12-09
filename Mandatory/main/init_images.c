/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:41:46 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 23:00:27 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ab_set_orn(t_data *data)
{
	if (data->plr->orn == 'E')
		data->plr->rot_angl = 0;
	else if (data->plr->orn == 'S')
		data->plr->rot_angl = M_PI / 2;
	else if (data->plr->orn == 'W')
		data->plr->rot_angl = M_PI;
	else if (data->plr->orn == 'N')
		data->plr->rot_angl = M_PI + (M_PI / 2);
}

void	init_images(t_data *data)
{
	data->win_img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (mlx_image_to_window(data->mlx, data->win_img, 0, 0) == -1)
		clean_exit(data, "Can't create image", 9);
}
