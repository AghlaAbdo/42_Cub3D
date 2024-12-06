/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:28:47 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/06 09:30:02 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"


void	ft_fll_chck(t_data *data, int flag)
{
	static int	flg_tww;

	if (flag && !flg_tww)
	{
		flg_tww = 1;
		if (data->map->no_txt == NULL || data->map->so_txt == NULL
			|| data->map->we_txt == NULL || data->map->ea_txt == NULL
			|| data->map->f[0] == -1 || data->map->f[1] == -1
			|| data->map->f[2] == -1 || data->map->c[0] == -1
			|| data->map->c[1] == -1 || data->map->c[2] == -1)
		{
			write(2, "Error\n", 6);
			write(2, "Missing information in the map file\n", 37);
			exit(1);
		}
		else
			ft_load_texture(data);
	}
}

void	set_wall_txtrs_null(t_data *data)
{
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->door_texture = NULL;
}

int	parse_file(t_data *data, char *file)
{
	t_maplst	*maplst;
	char		*line;
	int			flag;
	int			fd;

	maplst = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	set_wall_txtrs_null(data);
	flag = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!flag)
		{
			if (first_part(data, line))
				flag = 1;
		}
		ft_fll_chck(data, flag);
		if (flag)
			if (sec_part(data, &maplst, line))
				return (1);
		free(line);
	}
	close(fd);
	data->map->col = ab_maplst_size(maplst);
	ab_valid_map(data, maplst);
	return (0);
}
