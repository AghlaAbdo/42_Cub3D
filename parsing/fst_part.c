/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fst_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:39:25 by srachidi          #+#    #+#             */
/*   Updated: 2024/11/27 16:21:06 by aaghla           ###   ########.fr       */
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

void	sr_fc_check(t_data *data, char *line, int strt, char id)
{
	char	**rgb;
	int		i;

	i = 0;
	strt++;
	rgb = ft_split(sr_substr(line, strt, sr_len(line)), ',');
	while (rgb[i])
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
		{
			write(2, "Error \n", 8);
			write(2, "RGB color exceeds the rgb limit!\n", 34);
			exit (1);
		}
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
			exit (write (2, "NO texture config duplicate detected !\n", 40));
		else
			sr_id_check(data, line, i, "NO ");
	}
	else if (sr_strcmp(id, "SO"))
	{
		if (data->map->so_txt != NULL)
			exit (write (2, "SO texture config duplicate detected !\n", 40));
		else
			sr_id_check(data, line, i, "SO ");
	}
	else if (sr_strcmp(id, "WE"))
	{
		if (data->map->we_txt != NULL)
			exit (write (2, "WE texture config duplicate detected !\n", 40));
		else
			sr_id_check(data, line, i, "WE ");
	}
}

void	sr_nrm2(t_data *data, char *line, int i, char *id)
{
	if (sr_strcmp(id, "EA"))
	{
		if (data->map->ea_txt != NULL)
			exit (write (2, "EA texture config duplicate detected !\n", 40));
		else
			sr_id_check(data, line, i, "EA ");
	}
	else if (sr_strcmp(id, "F"))
	{
		if (data->map->f[0] != -1)
			exit (write (2, "F color config duplicate detected !\n", 37));
		else
			sr_fc_check(data, line, i, 'F');
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
	{
		if (data->map->c[0] != -1)
			exit (write (2, "C color config duplicate detected !\n", 37));
		else
			sr_fc_check(data, line, i, 'C');
	}
	else
		return (1);
	return (0);
}
