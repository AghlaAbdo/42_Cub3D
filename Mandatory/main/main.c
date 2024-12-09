/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:41:55 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/08 15:56:54 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		clean_exit_pars(&data, "Unable to create window", 3);
	init_images(&data);
	mlx_loop_hook(data.mlx, &ft_looper, &data);
	mlx_key_hook(data.mlx, &handle_events, &data);
	mlx_close_hook(data.mlx, &close_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
