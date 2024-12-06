/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:39:22 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/06 09:32:57 by aaghla           ###   ########.fr       */
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
			&& line[i] != 'S' && line[i] != 'D'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n')
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

	if (!data->map->ea_txt || !data->map->we_txt
		|| !data->map->so_txt || !data->map->no_txt)
		exit(99);
	if (!line)
		return (0);
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

static void	ab_fill_line(char *dst, char *src, int len)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	while (i < len)
		dst[i++] = ' ';
	dst[i] = '\0';
}

void	ab_is_closed(t_data *data, char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (ft_strchr(map[0], '0'))
		clean_exit_pars(data, "map not closed", 11);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'D')
			{
				if (!j || map[i][j - 1] == ' ' || map[i - 1][j] == ' '
					|| map[i][j + 1] == ' ' || map[i][j +1] == '\0'
					|| map[i +1][j] == ' ')
					clean_exit_pars(data, "map not closed", 12);
			}
			else if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!j || map[i][j - 1] == ' ' || map[i - 1][j] == ' '
					|| map[i][j + 1] == ' '
					|| map[i][j +1] == '\0' || map[i +1][j] == ' ')
					clean_exit_pars(data, "map not closed", 12);
				else
				{
					data->plr->y = i * MNMAP_TILE_S + (MNMAP_TILE_S / 2);
					data->plr->x = j * MNMAP_TILE_S + (MNMAP_TILE_S / 2);
					data->map->y = i * 24 + (24 / 2);
					data->map->x = j * 24 + (24 / 2);
					data->plr->orn = map[i][j];
				}
			}
			if (map[i][j] == 'D')
			{
				if (!j || !((map[i][j - 1] == '1' && map[i][j + 1] == '1')
					|| (map[i - 1][j] == '1'
					&& map[i + 1][j] == '1')))
					clean_exit_pars(data, "invalid door position", 82);
			}
		}
		if (!map[i + 2])
			break ;
	}
	if (ft_strchr(map[i + 1], '0'))
		clean_exit_pars(data, "map not closed", 13);
}

void	ab_valid_map(t_data *data, t_maplst *maplst)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	data->map->map = ft_malloc(sizeof(char *) * (data->map->col + 1), 0);
	while (++i < data->map->col)
		data->map->map[i] = ft_malloc(sizeof(char) * (data->map->row + 1), 0);
	data->map->map[i] = NULL;
	i = -1;
	while (++i < data->map->col)
	{
		ab_fill_line(data->map->map[i], maplst->line, data->map->row);
		maplst = maplst->next;
	}
	ab_is_closed(data, data->map->map);
}
