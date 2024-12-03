/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fst_part1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:39:28 by Apple             #+#    #+#             */
/*   Updated: 2024/12/01 15:42:48 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	sr_remover(t_data *data, char *id)
{
	if (sr_strcmp(id, "NO "))
		sr_rmv_nline(data->map->no_txt);
	else if (sr_strcmp(id, "SO "))
		sr_rmv_nline(data->map->so_txt);
	else if (sr_strcmp(id, "WE "))
		sr_rmv_nline(data->map->we_txt);
	else if (sr_strcmp(id, "EA "))
		sr_rmv_nline(data->map->ea_txt);
}

void	sr_id_check(t_data *data, char *line, int strt, char *id)
{
	strt += 2;
	while (line[strt] == ' ')
		strt++;
	if (sr_strcmp("NO ", id))
		data->map->no_txt = ft_strjoin(id,
				sr_substr(line, strt, sr_len(line)));
	else if (sr_strcmp("SO ", id))
		data->map->so_txt = ft_strjoin(id,
				sr_substr(line, strt, sr_len(line)));
	else if (sr_strcmp("WE ", id))
		data->map->we_txt = ft_strjoin(id,
				sr_substr(line, strt, sr_len(line)));
	else if (sr_strcmp("EA ", id))
		data->map->ea_txt = ft_strjoin(id,
				sr_substr(line, strt, sr_len(line)));
	sr_remover(data, id);
}
