/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:35:09 by Apple             #+#    #+#             */
/*   Updated: 2024/12/05 12:11:24 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	ft_clearcolorbuffer(t_data *data, uint32_t color)
{
	int	x;
	int	y;

	(void)color;
	x = 0;
	while (x < TXTR_W)
	{
		y = 0;
		while (y < TXTR_H)
		{
			if (x % 8 && y % 8)
				mlx_put_pixel(data->clrbfrtxtr, x, y,
					get_rgba(0, 0, 0, 255));
			else
				mlx_put_pixel(data->clrbfrtxtr, x, y,
					get_rgba(0, 0, 180, 255));
			y++;
		}
		x++;
	}
}

int	get_texture_x(t_data *data, t_rays *ray, int texture_width)
{
	double	wall_x;
	int		tex_x;

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
