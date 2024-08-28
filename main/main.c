/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:54:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/08/28 08:08:33 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->map = ft_malloc(sizeof(t_map), 0);
	data->plr = ft_malloc(sizeof(t_player), 0);
	data->map->c[0] = -1;
	data->map->f[0] = -1;
	data->map->ea_txt = NULL;
	data->map->so_txt = NULL;
	data->map->we_txt = NULL;
	data->map->no_txt = NULL;
	data->map->plr_nb = 0;
	data->map->row = 0;
	data->is_moving = 1;
}
void	ab_set_orn(t_data *data)
{
	// printf("orn: %c\n", data->plr->orn);
	if (data->plr->orn == 'E')
		data->plr->rot_angl = 0;
	else if (data->plr->orn == 'S')
		data->plr->rot_angl = M_PI / 2;
	else if (data->plr->orn == 'W')
		data->plr->rot_angl = M_PI;
	else if (data->plr->orn == 'N')
		data->plr->rot_angl = M_PI + (M_PI / 2);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	init_data(&data);
	if (parse_file(&data, av[1]))
		return (2);
	ab_set_orn(&data);
	data.mlx = mlx_init(WIN_W, WIN_H, "Cub3D", false);
	if (!data.mlx)
		clean_exit("Unable to create window", 3);
	data.map->mnmap_img = mlx_new_image(data.mlx, MNMAP_W, MNMAP_H);
	//  mlx_image_t* img2 = mlx_new_image(data.mlx, MNMAP_TILE_S, MNMAP_TILE_S);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    // ft_memset(data.map->mnmap_img->pixels, 250, data.map->mnmap_img->width * data.map->mnmap_img->height * sizeof(int32_t));
    // ft_memset(img2->pixels, 196, img2->width * img2->height * sizeof(int32_t));

    mlx_image_to_window(data.mlx, data.map->mnmap_img, 0, 0);
    // mlx_image_to_window(data.mlx, img2, 0, 0);
	// ab_minimap(&data);
	// for (int i = 0; data.map->map[i]; i++)
	// 	printf("%s\n", data.map->map[i]);
	// printf("\n\n");
	mlx_loop_hook(data.mlx, &ab_minimap, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
