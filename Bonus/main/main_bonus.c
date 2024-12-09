/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srachidi <srachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 09:41:55 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/08 11:01:24 by srachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	mlx_mouse_hook(data.mlx, &mse_evnt, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
