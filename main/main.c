/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:54:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/11/19 09:44:54 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_shade_bg(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			mlx_put_pixel(data->shade_bg, x, y, get_rgba(0, 0, 0, 120));
		}
	}
	data->shade_bg->enabled = false;
}

void	init_turning_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->frame = NULL;
	// anm->frames = (mlx_image_t **)ft_malloc(sizeof(mlx_image_t) * TRN_ON_FRMS, 0);
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t) * TRN_ON_FRMS, 0);
	i = -1;
	while (++i < TRN_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/turn_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 14);
		// anm->frames[i] = mlx_texture_to_image(data->mlx, txtr);
		// anm->frames[i]->enabled = false;
		// mlx_image_to_window(data->mlx, anm->frames[i], 475, WIN_H - 370);
		// mlx_delete_texture(txtr);
	}
	
}

void	init_idle_light_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = -1;
	// anm->txtrs = (mlx_image_t **)ft_malloc(sizeof(mlx_image_t) * IDLE_ON_FRMS, 0);
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t) * IDLE_ON_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < IDLE_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/idle_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 45);
		// anm->frames[i] = mlx_texture_to_image(data->mlx, anm->txtrs[i]);
		// anm->frames[i]->enabled = false;
		// mlx_delete_texture(anm->txtrs[i]);
		// mlx_image_to_window(data->mlx, anm->frames[i], 475, WIN_H - 370);
	}
}

void	init_turning_off_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t) * TRN_OFF_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < TRN_OFF_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/turn_light_off/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 51);
	// 	txtr = mlx_load_png(ft_strjoin(ft_strjoin("./images/turn_light_off/f_", ft_itoa(i)), ".png"));
	// 	if (!txtr)
	// 		clean_exit("Can't load png", 16);
	// 	anm->frames[i] = mlx_texture_to_image(data->mlx, txtr);
	// 	anm->frames[i]->enabled = false;
	// 	mlx_delete_texture(txtr);
	// 	mlx_image_to_window(data->mlx, anm->frames[i], 475, WIN_H - 370);
	}
}

void	init_walking_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t) * WALK_ON_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < WALK_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/walk_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 77);
	// 	txtr = mlx_load_png(ft_strjoin(ft_strjoin("./images/walk_light_on/f_", ft_itoa(i)), ".png"));
	// 	if (!txtr)
	// 		clean_exit("Can't load png", 17);
	// 	anm->frames[i] = mlx_texture_to_image(data->mlx, txtr);
	// 	anm->frames[i]->enabled = false;
	// 	mlx_image_to_window(data->mlx, anm->frames[i], 475, WIN_H - 370);
	// 	mlx_delete_texture(txtr);
	}
}

void	init_walking_off_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_image_t) * WALK_OFF_FRMS, 0);
	anm->frame = NULL;
	
	txtr = mlx_load_png(ft_strjoin(ft_strjoin("./images/walk_light_off/f_", ft_itoa(anm->curr_frm)), ".png"));
	if (!txtr)
		clean_exit("Can't load png", 88);
	anm->frame = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	mlx_image_to_window(data->mlx, anm->frame, 475, WIN_H - 370);

	i = -1;
	while (++i < WALK_OFF_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/walk_light_off/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 43);
	// 	// printf("loog i = %d\n", i);
	// 	txtr = mlx_load_png(ft_strjoin(ft_strjoin("./images/walk_light_off/f_", ft_itoa(i)), ".png"));
	// 	if (!txtr)
	// 		clean_exit("Can't load png", 88);
	// 	anm->frames[i] = mlx_texture_to_image(data->mlx, txtr);
	// 	anm->frames[i]->enabled = false;
	// 	mlx_image_to_window(data->mlx, anm->frames[i], 475, WIN_H - 370);
	// 	mlx_delete_texture(txtr);
	}
	// anm->frames[0]->enabled = true;
}

void	init_images(t_data *data)
{
	mlx_texture_t	*border;
	data->map->mnmap_img = mlx_new_image(data->mlx, MNMAP_W, MNMAP_H);
	data->win_img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->big_mnmp_img = mlx_new_image(data->mlx, BIG_MNMAP_W, BIG_MNMAP_H);
	data->shade_bg = mlx_new_image(data->mlx, WIN_W, WIN_H);
	draw_shade_bg(data);
	data->big_mnmp_img->enabled = false;
	mlx_image_to_window(data->mlx, data->win_img, 0, 0);
	mlx_image_to_window(data->mlx, data->map->mnmap_img, MNMAP_GAP, MNMAP_GAP);
	
	
	border = mlx_load_png("./images/mnmap_border.png");
	data->cross_txtr = mlx_load_png("./images/close.png");
	if (!data->cross_txtr || !border)
		clean_exit("Can't load png", 10);
	data->map->border = mlx_texture_to_image(data->mlx, border);
	mlx_delete_texture(border);
	mlx_image_to_window(data->mlx, data->map->border, MNMAP_GAP, MNMAP_GAP - 12);
	// data->map->border->enabled = false;

	data->cross_icon = mlx_texture_to_image(data->mlx, data->cross_txtr);
	data->cross_icon->enabled = false;
	data->hnd_cursr = mlx_create_std_cursor(MLX_CURSOR_HAND);


	init_turning_on_imgs(data, &data->trn_on_anm);
	init_turning_off_imgs(data, &data->trn_off_anm);
	init_idle_light_on_imgs(data, &data->idle_light_on_anm);
	init_walking_on_imgs(data, &data->walk_light_on_anm);
	init_walking_off_imgs(data, &data->walk_light_off_anm);

	border = mlx_load_png("./images/lighter_off.png");
	if (!border)
		clean_exit("Can't load png", 19);
	data->lighter_off = mlx_texture_to_image(data->mlx, border);
	mlx_delete_texture(border);
	mlx_image_to_window(data->mlx, data->lighter_off, WIN_W - 120, WIN_H - 150);
	border = mlx_load_png("./images/lighter_on.png");
	if (!border)
		clean_exit("Cna't load png", 20);
	data->lighter_on = mlx_texture_to_image(data->mlx, border);
	mlx_delete_texture(border);
	data->lighter_on->enabled = false;
	mlx_image_to_window(data->mlx, data->lighter_on, WIN_W - 120, WIN_H - 150);
	mlx_image_to_window(data->mlx, data->shade_bg, 0, 0);
	mlx_image_to_window(data->mlx, data->big_mnmp_img, WIN_W / 2 - BIG_MNMAP_W / 2, WIN_H / 2 - BIG_MNMAP_H / 2);
	mlx_image_to_window(data->mlx, data->cross_icon, WIN_W / 2 - BIG_MNMAP_W / 2, WIN_H / 2 - BIG_MNMAP_H / 2);
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
	data->map->plr_nb = 0;
	data->map->row = 0;
	data->is_moving = true;
	data->light = false;
	data->mouse = false;
	data->big_mnmap = false;
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

void	handle_events(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS && !data->big_mnmap)
	{
		if (!data->turning_on && data->light)
		{
			// data->idle_light_on_anm.frames[data->idle_light_on_anm.curr_frm]->enabled = false;
			mlx_delete_image(data->mlx, data->idle_light_on_anm.frame);
			data->idle_light_on_anm.frame = NULL;
			data->turning_off = true;
		}
		else if (!data->light)
		{
			data->turning_on = true;
		}
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		if (!data->big_mnmap)
			mlx_set_mouse_pos(data->mlx, WIN_W / 2, WIN_H / 2);
		data->ms_x = WIN_W / 2;
		data->mouse = !data->mouse;
		if (!data->mouse)
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		data->big_mnmap = !data->big_mnmap;
		if (data->big_mnmap)
		{
			data->map->mnmap_img->enabled = false;
			data->map->border->enabled = false;
			data->big_mnmp_img->enabled = true;
			data->cross_icon->enabled = true;
			data->shade_bg->enabled = true;
			data->map->y = data->plr->y;
			data->map->x = data->plr->x;
			data->map->p_y = BIG_MNMAP_H / 2;
			data->map->p_x = BIG_MNMAP_W / 2;
		}
		else
		{
			data->big_mnmp_img->enabled = false;
			data->map->mnmap_img->enabled = true;
			data->map->border->enabled = true;
			data->cross_icon->enabled = false;
			data->shade_bg->enabled = false;
			data->is_moving = true;
		}
	}
}

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
	init_images(&data);
	mlx_loop_hook(data.mlx, &ft_looper, &data);
	mlx_key_hook(data.mlx, &handle_events, &data);
	mlx_close_hook(data.mlx, &close_hook, &data);
	mlx_mouse_hook(data.mlx, &mouse_event, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
