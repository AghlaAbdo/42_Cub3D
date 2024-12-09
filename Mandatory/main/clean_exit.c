/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 18:06:50 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 22:58:55 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	delete_wall_txtrs(t_data *data)
{
	if (data->north_texture)
		mlx_delete_texture(data->north_texture);
	if (data->south_texture)
		mlx_delete_texture(data->south_texture);
	if (data->east_texture)
		mlx_delete_texture(data->east_texture);
	if (data->west_texture)
		mlx_delete_texture(data->west_texture);
}

void	clean_exit(t_data *data, char *err, int stat)
{
	delete_wall_txtrs(data);
	mlx_delete_image(data->mlx, data->win_img);
	ft_malloc(0, 1);
	if (stat)
		printf("Error\n%s\n", err);
	exit(stat);
}

void	clean_exit_pars(t_data *data, char *err, int stat)
{
	delete_wall_txtrs(data);
	ft_malloc(0, 1);
	printf("Error\n%s\n", err);
	exit(stat);
}

void	close_hook(void	*param)
{
	clean_exit((t_data *)param, "All good", 0);
}
