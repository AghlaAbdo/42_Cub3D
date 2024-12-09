/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fst_part1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:42:21 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 21:29:09 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

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
		data->map->no_txt = sr_substr(line, strt, sr_len(line));
	else if (sr_strcmp("SO ", id))
		data->map->so_txt = sr_substr(line, strt, sr_len(line));
	else if (sr_strcmp("WE ", id))
		data->map->we_txt = sr_substr(line, strt, sr_len(line));
	else if (sr_strcmp("EA ", id))
		data->map->ea_txt = sr_substr(line, strt, sr_len(line));
	sr_remover(data, id);
}

int	ft_is_strt(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (1);
	while (line[++i] == ' ')
		;
	if (line[i] == ',')
		return (1);
	return (0);
}

int	ft_is_end(char *line)
{
	int	ln;

	ln = 0;
	if (!line)
		return (1);
	ln = sr_len(line);
	while (line[--ln] == ' ' || line[ln] == '\n')
		;
	if (line[ln] == ',')
		return (1);
	return (0);
}

int	sr_is_vld(char *line)
{
	int	i;
	int	cms;

	cms = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == ',')
			cms++;
		if (cms > 2)
			return (1);
		if (line[i] != ' ' && line[i] != ',' && line[i] != '\n')
			if (!ft_isdigit(line[i]))
				return (1);
	}
	if (ft_is_strt(line) || ft_is_end(line))
		return (1);
	return (0);
}
