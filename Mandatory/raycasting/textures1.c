/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:42:58 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 23:09:36 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	ft_clearcolorbuffer(t_data *data, uint32_t color)
{
	int	x;
	int	y;

	(void)data;
	(void)color;
	x = 0;
	while (x < TXTR_W)
	{
		y = 0;
		while (y < TXTR_H)
		{
			y++;
		}
		x++;
	}
}

int	get_texture_x(t_data *data, t_rays *ray, int texture_width)
{
	double	wall_x;
	int		tex_x;

	(void)data;
	if (ray->orn == 'h')
	{
		wall_x = ray->x;
		if (!ray->is_up)
			wall_x = MNMAP_TILE_S - fmod(wall_x, MNMAP_TILE_S);
	}
	else
	{
		wall_x = ray->y;
		if (ray->is_left)
			wall_x = MNMAP_TILE_S - fmod(wall_x, MNMAP_TILE_S);
	}
	tex_x = (int)(fmod(wall_x, MNMAP_TILE_S) / MNMAP_TILE_S * texture_width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture_width)
		tex_x = texture_width - 1;
	return (tex_x);
}
