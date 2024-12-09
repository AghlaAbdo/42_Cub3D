/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fst_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:39:25 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/07 12:39:22 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

void	sr_fc_check(t_data *data, char *line, int strt, char id)
{
	char	**rgb;
	int		i;

	i = 0;
	strt++;
	if (sr_is_vld(sr_substr(line, strt, sr_len(line))))
		clean_exit_pars(data, "invalid RGB structure !\n", 88);
	rgb = ft_split(sr_substr(line, strt, sr_len(line)), ',');
	while (rgb[i])
	{
		if (i >= 3 || ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			clean_exit_pars(data, "Invalid RGB color format", 89);
		else
		{
			if (id == 'F')
				data->map->f[i] = ft_atoi(rgb[i]);
			else
				data->map->c[i] = ft_atoi(rgb[i]);
		}
		i++;
	}
}

void	sr_nrm1(t_data *data, char *line, int i, char *id)
{
	if (sr_strcmp(id, "NO"))
	{
		if (data->map->no_txt != NULL)
			clean_exit_pars(data, "NO texture config duplicate detected!", 60);
		else
			sr_id_check(data, line, i, "NO ");
	}
	else if (sr_strcmp(id, "SO"))
	{
		if (data->map->so_txt != NULL)
			clean_exit_pars(data, "SO texture config duplicate detected!", 61);
		else
			sr_id_check(data, line, i, "SO ");
	}
	else if (sr_strcmp(id, "WE"))
	{
		if (data->map->we_txt != NULL)
			clean_exit_pars(data, "WE texture config duplicate detected!", 62);
		else
			sr_id_check(data, line, i, "WE ");
	}
}

void	sr_nrm2(t_data *data, char *line, int i, char *id)
{
	if (sr_strcmp(id, "EA"))
	{
		if (data->map->ea_txt != NULL)
			clean_exit_pars(data, "EA texture config duplicate detected!", 63);
		else
			sr_id_check(data, line, i, "EA ");
	}
	else if (sr_strcmp(id, "F"))
	{
		if (data->map->f[0] != -1)
			clean_exit_pars(data, "F color config duplicate detected!", 64);
		else
			sr_fc_check(data, line, i, 'F');
	}
	else
	{
		if (data->map->c[0] != -1)
			clean_exit_pars(data, "C color config duplicate detected!", 65);
		else
			sr_fc_check(data, line, i, 'C');
	}
}

int	first_part(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (sr_strcmp(sr_substr(line, i, 2), "NO"))
		sr_nrm1(data, line, i, "NO");
	else if (sr_strcmp(sr_substr(line, i, 2), "SO"))
		sr_nrm1(data, line, i, "SO");
	else if (sr_strcmp(sr_substr(line, i, 2), "WE"))
		sr_nrm1(data, line, i, "WE");
	else if (sr_strcmp(sr_substr(line, i, 2), "EA"))
		sr_nrm2(data, line, i, "EA");
	else if (sr_strcmp(sr_substr(line, i, 1), "F"))
		sr_nrm2(data, line, i, "F");
	else if (sr_strcmp(sr_substr(line, i, 1), "C"))
		sr_nrm2(data, line, i, "C");
	else if (sr_strcmp(line, "\n"))
		return (0);
	else
		return (1);
	return (0);
}
