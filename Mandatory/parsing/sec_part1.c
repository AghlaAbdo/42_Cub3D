/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_part1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thedon <thedon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:53:48 by srachidi          #+#    #+#             */
/*   Updated: 2025/04/06 11:41:04 by thedon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

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
		data->plr->orn = map[i][j];
	}
}

static void	is_map_closed(t_data *data, char **map, int i, int j)
{
	if (ft_strchr(map[0], '0'))
		clean_exit_pars(data, "map not closed", 11);
	while (map[i][++j])
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			clean_exit_pars(data, "map is not closeddd", 12);
	}
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				check_char_surounding(data, map, i, j);
		}
		if (!map[i + 2])
			break ;
	}
	if (ft_strchr(map[i + 1], '0') || ft_strchr(map[i + 1], 'D')
		|| ft_strchr(map[i + 1], 'N') || ft_strchr(map[i + 1], 'S')
		|| ft_strchr(map[i + 1], 'W') || ft_strchr(map[i + 1], 'E'))
		clean_exit_pars(data, "map not closed", 13);
}

static void	check_plr_exist(t_data *data, char **map)
{
	int	i;
	int	j;
	int	plr;

	plr = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				plr = 1;
				break ;
			}
		}
	}
	if (!plr)
		clean_exit_pars(data, "Player doesn't exist", 2);
}

void	ab_valid_map(t_data *data, t_maplst *maplst)
{
	int	i;

	i = -1;
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
