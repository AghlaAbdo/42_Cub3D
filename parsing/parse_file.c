/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:28:47 by aaghla            #+#    #+#             */
/*   Updated: 2024/08/19 15:04:47 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/cub3d.h"

int	parse_file(t_data *data, char *file)
{
	t_maplst	*maplst;
	char	*line;
	int		flag;
	int		fd;

	maplst = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	flag = 1;
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!flag)
		{
			if (first_part(data, line))
				flag = 1;
		}
		else
			if (sec_part(data, &maplst, line))
				return (1);
		free(line);
	}
	data->map->col = ab_maplst_size(maplst);
	ab_valid_map(data, maplst);
	// printf("plr_nb: %d\nmaxline: %d\nlst size: %d\n", data->map->plr_nb,
	// 	data->map->row, ab_maplst_size(maplst));
	// while (maplst)
	// {
	// 	printf("%s\n", maplst->line);
	// 	maplst = maplst->next;
	// }
	return (0);
}
