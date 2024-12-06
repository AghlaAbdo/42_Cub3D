/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Apple <Apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:57:23 by aaghla            #+#    #+#             */
/*   Updated: 2024/12/05 19:26:30 by Apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	init_ligher_imgs(t_data *data)
{
	mlx_texture_t	*txtr;

	txtr = mlx_load_png("./images/lighter_off.png");
	if (!txtr)
		clean_exit(data, "Can't load png", 19);
	data->lighter_off = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	txtr = mlx_load_png("./images/lighter_on.png");
	if (!txtr)
		clean_exit(data, "Cna't load png", 20);
	data->lighter_on = mlx_texture_to_image(data->mlx, txtr);
	mlx_delete_texture(txtr);
	data->lighter_on->enabled = false;
	if (mlx_image_to_window(data->mlx, data->lighter_off, WIN_W - 120,
			WIN_H - 150) || mlx_image_to_window(data->mlx, data->lighter_on,
			WIN_W - 120, WIN_H - 150))
		clean_exit(data, "Cant put image to window", 21);
}

static void	set_black_bg(t_data *data)
{
	int	y;
	int	x;

	data->black_bg = mlx_new_image(data->mlx, WIN_W, WIN_H);
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			mlx_put_pixel(data->black_bg, x, y, get_rgba(0, 0, 0, 255));
	}
	mlx_image_to_window(data->mlx, data->black_bg, 0, 0);
}

void	init_images(t_data *data)
{
	set_black_bg(data);
	data->map->mnmap_img = mlx_new_image(data->mlx, MNMAP_W, MNMAP_H);
	data->win_img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (mlx_image_to_window(data->mlx, data->win_img, 0, 0) == -1
		|| mlx_image_to_window(data->mlx, data->map->mnmap_img,
			MNMAP_GAP, MNMAP_GAP) == -1)
		clean_exit(data, "Can't create image", 9);
	data->map->border_txt = mlx_load_png("./images/mnmap_border.png");
	data->map->cross_txt = mlx_load_png("./images/close.png");
	if (!data->map->cross_txt || !data->map->border_txt)
		clean_exit(data, "Can't load png", 10);
	data->map->border_img = mlx_texture_to_image(
			data->mlx, data->map->border_txt);
	mlx_image_to_window(data->mlx, data->map->border_img,
		MNMAP_GAP, MNMAP_GAP - 12);
	data->hnd_cursr = mlx_create_std_cursor(MLX_CURSOR_HAND);
	init_turning_on_imgs(data, &data->trn_on_anm);
	init_turning_off_imgs(data, &data->trn_off_anm);
	init_idle_light_on_imgs(data, &data->idle_light_on_anm);
	init_walking_on_imgs(data, &data->walk_light_on_anm);
	init_walking_off_imgs(data, &data->walk_light_off_anm);
	init_ligher_imgs(data);
}
