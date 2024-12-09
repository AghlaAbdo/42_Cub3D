/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_part1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:53:48 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/08 15:01:10 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d_bonus.h"

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

static void	check_char_surounding(t_data *data, char **map, int i, int j)
{
	if (!j || map[i][j - 1] == ' ' || map[i - 1][j] == ' '
		|| map[i][j + 1] == ' ' || map[i][j +1] == '\0'
		|| map[i + 1][j] == ' ')
		clean_exit_pars(data, "map not closed", 12);
	if (map[i][j] == 'N' || map[i][j] == 'S'
		|| map[i][j] == 'E' || map[i][j] == 'W')
	{
		data->plr->y = i * MNMAP_TILE_S + (MNMAP_TILE_S / 2);
		data->plr->x = j * MNMAP_TILE_S + (MNMAP_TILE_S / 2);
		data->map->y = i * 24 + (24 / 2);
		data->map->x = j * 24 + (24 / 2);
		data->plr->orn = map[i][j];
	}
}

void	first_line(t_data *data, char **map, int i, int j)
{
	while (map[i][++j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			clean_exit_pars(data, "map is not closeddd", 12);
	}
}

static void	is_map_closed(t_data *data, char **map, int i, int j)
{
	first_line(data, map, i, j);
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'D' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				check_char_surounding(data, map, i, j);
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
	if (ft_strchr(map[i + 1], '0') || ft_strchr(map[i + 1], 'D')
		|| ft_strchr(map[i + 1], 'N') || ft_strchr(map[i + 1], 'S')
		|| ft_strchr(map[i + 1], 'W') || ft_strchr(map[i + 1], 'E'))
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
	check_plr_exist(data, data->map->map);
	is_map_closed(data, data->map->map, 0, -1);
}
