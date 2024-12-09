/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:49:38 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/07 23:07:08 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*get_data(t_data *curr_data)
{
	static t_data	*data;

	if (!curr_data)
		return (data);
	data = curr_data;
	return (data);
}

void	init_data_nrm(t_data *data)
{
	data->map->c[0] = -1;
	data->map->c[1] = -1;
	data->map->c[2] = -1;
	data->map->f[0] = -1;
	data->map->f[1] = -1;
	data->map->f[2] = -1;
}

static void	allocate_memory(t_data *data)
{
	data->map = ft_malloc(sizeof(t_map), 0);
	data->plr = ft_malloc(sizeof(t_player), 0);
	get_data(data);
}

void	init_data(t_data *data)
{
	allocate_memory(data);
	init_data_nrm(data);
	data->map->ea_txt = NULL;
	data->map->so_txt = NULL;
	data->map->we_txt = NULL;
	data->map->no_txt = NULL;
	data->map->plr_nb = 0;
	data->map->row = 0;
	data->is_moving = true;
	data->rendering = true;
}
