/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:54:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/03 21:35:33 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit_init(t_data *data, char *err, int stat)
{
	delete_wall_txtrs(data);
	ft_malloc(0, 1);
	printf("Error\n%s\n", err);
	exit(stat);
}
void	init_ligher_imgs(t_data *data)
{
	mlx_texture_t	*txtr;

	txtr = mlx_load_png("./images/lighter_off.png");
	if (!txtr)
		clean_exit_init(data, "Can't load png", 19);
	data->lighter_off = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	txtr = mlx_load_png("./images/lighter_on.png");
	if (!txtr)
		clean_exit_init(data, "Cna't load png", 20);
	data->lighter_on = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	data->lighter_on->enabled = false;
	mlx_image_to_window(data->mlx, data->lighter_off, WIN_W - 120, WIN_H - 150);
	mlx_image_to_window(data->mlx, data->lighter_on, WIN_W - 120, WIN_H - 150);
}


void	init_images(t_data *data)
{
	ft_load_texture(data);
	mlx_delete_image(data->mlx, NULL);
	data->map->mnmap_img = mlx_new_image(data->mlx, MNMAP_W, MNMAP_H);
	data->win_img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (mlx_image_to_window(data->mlx, data->win_img, 0, 0) == -1
		|| mlx_image_to_window(data->mlx, data->map->mnmap_img, MNMAP_GAP, MNMAP_GAP) == -1)
		clean_exit_init(data, "Can't create image", 9);
	data->map->border_txt = mlx_load_png("./images/mnmap_border.png");
	data->map->cross_txt = mlx_load_png("./images/close.png");
	data->map->border_img = mlx_texture_to_image(data->mlx, data->map->border_txt);
	if (!data->map->cross_txt || !data->map->border_txt
		|| mlx_image_to_window(data->mlx, data->map->border_img, MNMAP_GAP, MNMAP_GAP - 12))
	{
		mlx_delete_image(data->mlx, data->map->mnmap_img);
		mlx_delete_image(data->mlx, data->win_img);
		clean_exit_init(data, "Can't load png", 10);
	}
	data->hnd_cursr = mlx_create_std_cursor(MLX_CURSOR_HAND);
	init_turning_on_imgs(data, &data->trn_on_anm);
	init_turning_off_imgs(data, &data->trn_off_anm);
	init_idle_light_on_imgs(data, &data->idle_light_on_anm);
	init_walking_on_imgs(data, &data->walk_light_on_anm);
	init_walking_off_imgs(data, &data->walk_light_off_anm);
	init_ligher_imgs(data);
}

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
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->door_texture = NULL;
	data->map->plr_nb = 0;
	data->map->row = 0;
	data->is_moving = true;
	data->rendering = true;
	data->light = false;
	data->mouse = false;
	data->bigmap = false;
	data->turning_on = false;
	data->turning_off = false;
	data->idle_on = false;
	data->walking_on = false;
	data->walking_off = false;
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

void	close_hook(void	*param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	i = -1;
	while (++i < TRN_ON_FRMS)
		mlx_delete_texture(data->trn_on_anm.txtrs[i]);
	i = -1;
	while (++i < TRN_OFF_FRMS)
		mlx_delete_texture(data->trn_off_anm.txtrs[i]);
	i = -1;
	while (++i < IDLE_ON_FRMS)
		mlx_delete_texture(data->idle_light_on_anm.txtrs[i]);
	i = -1;
	while (++i < WALK_ON_FRMS)
		mlx_delete_texture(data->walk_light_on_anm.txtrs[i]);
	i = -1;
	while (++i < WALK_OFF_FRMS)
		mlx_delete_texture(data->walk_light_off_anm.txtrs[i]);
	mlx_delete_image(data->mlx, data->lighter_on);
	mlx_delete_image(data->mlx, data->lighter_off);
	ft_malloc(0, 1);
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
		clean_exit_pars("Unable to create window", 3);
	init_images(&data);
	mlx_loop_hook(data.mlx, &ft_looper, &data);
	mlx_key_hook(data.mlx, &handle_events, &data);
	mlx_close_hook(data.mlx, &close_hook, &data);
	mlx_mouse_hook(data.mlx, &mouse_event, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
