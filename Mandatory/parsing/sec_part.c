/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:39:22 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/08 15:05:13 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

static int	ab_check_chars(char *line, t_data *data)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (1);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ' && line[i] != '\n')
			return (1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			data->map->plr_nb++;
		i++;
	}
	if (data->map->plr_nb > 1)
		clean_exit_pars(data, "More than one player postion", 10);
	return (0);
}

int	sec_part(t_data *data, t_maplst **maplst, char *line)
{
	int	len;
	int	i;

	if (line[0] == '\n')
		clean_exit_pars(data, "empty line in map", 7);
	i = -1;
	while (line[++i] && line[i] != '\n')
		;
	while (line[--i] == ' ')
		;
	line[i +1] = '\0';
	if (!(i + 1))
		clean_exit_pars(data, "empty line in map", 8);
	len = i + 1;
	if (len > data->map->row)
		data->map->row = len;
	if (ab_check_chars(line, data))
		clean_exit_pars(data, "unknown characters in map", 9);
	ab_maplstaddb(maplst, ab_maplst_new(ft_strdup(line)));
	return (0);
}
