/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:54:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/09/06 10:01:08 by aaghla           ###   ########.fr       */
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
	data->is_moving = true;
	data->light = false;
	data->mouse = false;
}

// set Player orientaion
void	ab_set_orn(t_data *data)
{
	if (data->plr->orn == 'E')
		data->plr->rot_angl = 0;
	else if (data->plr->orn == 'S')
		data->plr->rot_angl = M_PI / 2;
	else if (data->plr->orn == 'W')
		data->plr->rot_angl = M_PI;
	else if (data->plr->orn == 'N')
		data->plr->rot_angl = M_PI + (M_PI / 2);
}

void	turn_light(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS)
		data->light = !data->light;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		mlx_set_mouse_pos(data->mlx, WIN_W / 2, WIN_H / 2);
		data->ms_x = WIN_W / 2;
		data->mouse = !data->mouse;
		if (!data->mouse)
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
}

// void	mouse_handle(double x, double y, void *param)
// {
// 	t_data	*data;
	
// }

void	close_hook(void	*param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)data;
	exit(0);
}

void	leaks()
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	// atexit(leaks);
	init_data(&data);
	if (parse_file(&data, av[1]))
		return (2);
	ab_set_orn(&data);
	data.mlx = mlx_init(WIN_W, WIN_H, "Cub3D", false);
	if (!data.mlx)
		clean_exit("Unable to create window", 3);
	data.map->mnmap_img = mlx_new_image(data.mlx, MNMAP_W, MNMAP_H);
	data.ray_img = mlx_new_image(data.mlx, MNMAP_W, MNMAP_H);
	data.win_img = mlx_new_image(data.mlx, WIN_W, WIN_H);
	mlx_image_to_window(data.mlx, data.win_img, 0, 0);
    mlx_image_to_window(data.mlx, data.map->mnmap_img, 0, 0);
	mlx_image_to_window(data.mlx, data.ray_img, 0, 0);
	mlx_loop_hook(data.mlx, &ft_looper, &data);
	mlx_key_hook(data.mlx, &turn_light, &data);
	mlx_close_hook(data.mlx, &close_hook, &data);
	// mlx_mouse_hook(data.mlx, &mouse_handle, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
