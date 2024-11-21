/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:54:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/11/21 10:06:23 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_turning_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = 0;
	anm->frame = NULL;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t) * TRN_ON_FRMS, 0);
	i = -1;
	while (++i < TRN_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/turn_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 14);
	}
	
}

void	init_idle_light_on_imgs(t_data *data, t_animation *anm)
{
	mlx_texture_t	*txtr;
	int				i;

	anm->last_frm_time = mlx_get_time() * 1e3;
	anm->curr_frm = -1;
	anm->txtrs = (mlx_texture_t **)ft_malloc(sizeof(mlx_texture_t) * IDLE_ON_FRMS, 0);
	anm->frame = NULL;
	i = -1;
	while (++i < IDLE_ON_FRMS)
	{
		anm->txtrs[i] = mlx_load_png(ft_strjoin(ft_strjoin("./images/idle_light_on/f_", ft_itoa(i)), ".png"));
		if (!anm->txtrs[i])
			clean_exit("Can't load png", 45);
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
	}
}

void	init_images(t_data *data)
{
	mlx_texture_t	*txtr;
	data->map->mnmap_img = mlx_new_image(data->mlx, MNMAP_W, MNMAP_H);
	data->win_img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	mlx_image_to_window(data->mlx, data->win_img, 0, 0);
	mlx_image_to_window(data->mlx, data->map->mnmap_img, MNMAP_GAP, MNMAP_GAP);
	
	
	data->map->border_txt = mlx_load_png("./images/mnmap_border.png");
	data->map->cross_txt = mlx_load_png("./images/close.png");
	if (!data->map->cross_txt || !data->map->border_txt)
		clean_exit("Can't load png", 10);
	data->map->border_img = mlx_texture_to_image(data->mlx, data->map->border_txt);
	// mlx_delete_texture(border);
	mlx_image_to_window(data->mlx, data->map->border_img, MNMAP_GAP, MNMAP_GAP - 12);
	// data->map->border->enabled = false;

	// data->map->cross_img = mlx_texture_to_image(data->mlx, data->map->cross_txt);
	// data->map->cross_img->enabled = false;
	data->hnd_cursr = mlx_create_std_cursor(MLX_CURSOR_HAND);


	init_turning_on_imgs(data, &data->trn_on_anm);
	init_turning_off_imgs(data, &data->trn_off_anm);
	init_idle_light_on_imgs(data, &data->idle_light_on_anm);
	init_walking_on_imgs(data, &data->walk_light_on_anm);
	init_walking_off_imgs(data, &data->walk_light_off_anm);

	txtr = mlx_load_png("./images/lighter_off.png");
	if (!txtr)
		clean_exit("Can't load png", 19);
	data->lighter_off = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	mlx_image_to_window(data->mlx, data->lighter_off, WIN_W - 120, WIN_H - 150);
	txtr = mlx_load_png("./images/lighter_on.png");
	if (!txtr)
		clean_exit("Cna't load png", 20);
	data->lighter_on = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	data->lighter_on->enabled = false;
	mlx_image_to_window(data->mlx, data->lighter_on, WIN_W - 120, WIN_H - 150);
	// mlx_image_to_window(data->mlx, data->map->cross_img, WIN_W / 2 - BIGMAP_W / 2, WIN_H / 2 - BIGMAP_H / 2);
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

void	switch_light(t_data *data)
{
	if (!data->turning_on && data->light)
	{
		if (data->idle_on)
		{
			mlx_delete_image(data->mlx, data->idle_light_on_anm.frame);
			data->idle_light_on_anm.frame = NULL;
		}
		data->turning_off = true;
	}
	else if (!data->light)
		data->turning_on = true;
}

void	show_big_map(t_data *data)
{
	data->bigmap = true;
	data->map->mnmap_img->enabled = false;
	data->map->border_img->enabled = false;
	data->shade_bg = mlx_new_image(data->mlx, WIN_W, WIN_H);
	draw_shade_bg(data);
	data->bigmap_img = mlx_new_image(data->mlx, BIGMAP_W, BIGMAP_H);
	data->map->cross_img = mlx_texture_to_image(data->mlx, data->map->cross_txt);
	if (!data->shade_bg || !data->bigmap_img || !data->map->cross_img)
		close_hook(data);
	if (mlx_image_to_window(data->mlx, data->shade_bg, 0, 0) == -1
		|| mlx_image_to_window(data->mlx, data->bigmap_img, WIN_W / 2 - BIGMAP_W / 2,
		WIN_H / 2 - BIGMAP_H / 2) == -1 || mlx_image_to_window(data->mlx, data->map->cross_img,
		WIN_W / 2 - BIGMAP_W / 2, WIN_H / 2 - BIGMAP_H / 2) == -1)
		close_hook(data);
	data->map->y = data->plr->y;
	data->map->x = data->plr->x;
	data->map->p_y = BIGMAP_H / 2;
	data->map->p_x = BIGMAP_W / 2;
}

void	hide_big_map(t_data *data)
{
	data->bigmap = false;
	mlx_delete_image(data->mlx, data->bigmap_img);
	mlx_delete_image(data->mlx, data->shade_bg);
	mlx_delete_image(data->mlx, data->map->cross_img);
	data->map->mnmap_img->enabled = true;
	data->map->border_img->enabled = true;
	// data->map->cross_img->enabled = false;
	data->rendering = true;
}

void	handle_events(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		close_hook(param);
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS && !data->bigmap)
		switch_light(data);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		if (!data->bigmap)
			mlx_set_mouse_pos(data->mlx, WIN_W / 2, WIN_H / 2);
		data->ms_x = WIN_W / 2;
		data->mouse = !data->mouse;
		if (!data->mouse)
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	}
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		data->bigmap = !data->bigmap;
		if (data->bigmap)
			show_big_map(data);
		else
			hide_big_map(data);
	}
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
