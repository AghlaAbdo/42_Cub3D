/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:28:47 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/08 15:55:48 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

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
			clean_exit_pars(data, "Missing information in the map file", 37);
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

int	ft_nrm_prs_fl(int *flag, t_data *data, t_maplst **maplst, char *line)
{
	if (!*flag)
	{
		if (first_part(data, line))
			*flag = 1;
	}
	ft_fll_chck(data, *flag);
	if (*flag)
		if (sec_part(data, maplst, line))
			return (1);
	return (0);
}

void	check_file_ext(t_data *data, char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	while (i && file[i] != '.')
		i--;
	if (ft_strncmp(file + i, ".cub", 5))
		clean_exit_pars(data, "Invalid file format", 3);
}

int	parse_file(t_data *data, char *file)
{
	t_maplst	*maplst;
	char		*line;
	int			flag;
	int			fd;

	maplst = NULL;
	fd = open(file, O_RDONLY);
	set_wall_txtrs_null(data);
	check_file_ext(data, file);
	if (fd == -1)
		clean_exit_pars(data, "Can't find config file", 2);
	flag = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_nrm_prs_fl(&flag, data, &maplst, line))
			return (1);
		free(line);
	}
	close(fd);
	data->map->col = ab_maplst_size(maplst);
	ab_valid_map(data, maplst);
	return (0);
}
