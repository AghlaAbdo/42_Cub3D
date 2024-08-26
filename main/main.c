/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:54:05 by srachidi          #+#    #+#             */
/*   Updated: 2024/08/26 17:42:20 by aaghla           ###   ########.fr       */
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
	data->plr->rot_angl = M_PI  / 2;
}
void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	// printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	check_pixel(t_data *data, int y, int x)
{
	int	i;
	int	j;

	i = (data->plr->y + y) / MNMAP_TILE_S -3;
	j = (data->plr->x + x) / MNMAP_TILE_S -4;
	if (i < 0 || j < 0 || i >= data->map->col || j >= data->map->row)
		return (-1);
	if (data->map->map[i][j] == '1')
		return (1);
	else if (data->map->map[i][j] == '0' || data->map->map[i][j] == 'N'
		|| data->map->map[i][j] == 'S' || data->map->map[i][j] == 'E'
		|| data->map->map[i][j] == 'W')
		return (0);
	return (-1);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void drawLine(t_data *data, int x1, int x2, int y) {
    for (int i = x1; i <= x2; i++) {
        mlx_put_pixel(data->map->mnmap_img, i, y, get_rgba(238, 238, 238, 255));
    }
}

// Function to fill a circle using the Midpoint Circle Algorithm
void draw_circle(t_data *data, int h, int k, int r) {
    int x = 0;
    int y = r;
    int d = 1 - r; // Initial decision parameter

    // Draw and fill the circle
    while (x <= y) {
        // Plot the lines between the points in the octants
        drawLine(data, h - x, h + x, k + y);
        drawLine(data, h - x, h + x, k - y);
        drawLine(data, h - y, h + y, k + x);
        drawLine(data, h - y, h + y, k - x);

        // Update the decision parameter based on the midpoint
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

int	check_wall(t_data *data, int p_x, int p_y)
{
	int	x;
	int	y;
	int	deg;
	int	r;
	int	temp1;
	int	temp2;

	// printf("p_y: %d | p_x: %d\n", p_y, p_x);
	deg = 0;
	r = 7;
	while (deg < 360)
	{
		temp1 = r * sin(deg);
		temp2 = r * cos(deg);
		y = temp1 + p_y;
		x = temp2 + p_x;
		temp1 += MNMAP_H / 2;
		temp2 += MNMAP_W / 2;
		// printf("x: %d | y: %d\n", x/ MNMAP_TILE_S, y/ MNMAP_TILE_S);
		mlx_put_pixel(data->map->mnmap_img, temp2, temp1, get_rgba(255, 255, 0, 255));
		if (data->map->map[y / MNMAP_TILE_S][x / MNMAP_TILE_S] == '1')
			return (1);
		deg++;
	}
	return (0);
}

void plot(t_data *data, int x, int y) {
   mlx_put_pixel(data->map->mnmap_img, x, y, get_rgba(255, 0, 0, 255));
}

void ab_drawline(t_data *data, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        plot(data, x1, y1);
        if (x1 == x2 && y1 == y2) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}

// void ab_drawline(t_data *data, int x1, int y1, int x2, int y2) {
//     int dx = x2 - x1;
// 	if (dx < 0)
// 		dx = -dx;
//     int dy = y2 - y1;
// 	if (dy < 0)
// 		dy = -dy;
//     int sx = x1 < x2 ? 1 : -1;
//     int sy = y1 < y2 ? 1 : -1;
//     int err = dx - dy;

//     while (1) {
//         mlx_put_pixel(data->map->mnmap_img,x1, y1, get_rgba(255, 0, 255, 255));  // Plot the pixel at (x1, y1)

//         if (x1 == x2 && y1 == y2) break;
//         int e2 = 2 * err;

//         if (e2 > -dy) {
//             err -= dy;
//             x1 += sx;
//         }

//         if (e2 < dx) {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }

void	ab_minimap(void *param)
{
	int	i;
	int	j;
	int	p_y;
	int	p_x;
	int x;
	int	y;
	t_data	*data;

	data = (t_data *)param;
	p_y = -1;
	while (++p_y < MNMAP_H)
	{
		p_x = -1;
		while (++p_x < MNMAP_W)
		{
			if (check_pixel(data, p_y, p_x ) == 1)
				mlx_put_pixel(data->map->mnmap_img, p_x, p_y, get_rgba(32, 30, 67, 255));
			else if (check_pixel(data, p_y, p_x) == 0)
				mlx_put_pixel(data->map->mnmap_img, p_x, p_y, get_rgba(19, 75, 112, 255));
			else
				mlx_put_pixel(data->map->mnmap_img, p_x, p_y, get_rgba(80, 140, 155, 255));
		}
	}
	p_y = (MNMAP_H / 2) ;
	p_x = (MNMAP_W / 2) ;
	draw_circle(data, p_x, p_y, 3);
	check_wall(data, data->plr->x, data->plr->y);
	ab_drawline(data, p_x, p_y, p_x + (cos(data->plr->rot_angl) * 40), p_y + (sin(data->plr->rot_angl) * 40));
	// i = -1;
	// j = 5;
	// while (++i < 8)
	// {
	// 	j--;
	// 	x = j;
	// 	while (x <= 8)
	// 		mlx_put_pixel(data->map->mnmap_img, p_x + x++, p_y + i, 3218705511);
	// }
}


void	ab_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_D)
	// {
	// 	data->plr->y -= MOVE_SPD;
	// 	data->plr->x += MOVE_SPD;
	// }
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		// if (!check_wall(data, data->plr->x, data->plr->y - MOVE_SPD))
		printf("plr->y bef: %d | plr->x bef: %d\n", data->plr->y, data->plr->x);
		data->plr->y += sin(data->plr->rot_angl) * MOVE_SPD;
		data->plr->x += cos(data->plr->rot_angl) * MOVE_SPD;
		printf("plr->y aft: %d | plr->x aft: %d\n\n", data->plr->y, data->plr->x);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (!check_wall(data, data->plr->x -MOVE_SPD, data->plr->y))
		data->plr->x -= MOVE_SPD;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (!check_wall(data, data->plr->x, data->plr->y + MOVE_SPD))
			data->plr->y += cos(data->plr->rot_angl) * MOVE_SPD;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		if (!check_wall(data, data->plr->x + MOVE_SPD, data->plr->y))
			data->plr->x += MOVE_SPD;
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->plr->rot_angl += ROT_SPD * -1;
	}
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		data->plr->rot_angl += ROT_SPD;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	init_data(&data);
	if (parse_file(&data, av[1]))
		return (2);
	data.mlx = mlx_init(1200, 675, "Cub3D", false);
	if (!data.mlx)
		clean_exit("Unable to create window", 3);
	data.map->mnmap_img = mlx_new_image(data.mlx, MNMAP_W, MNMAP_H);
	//  mlx_image_t* img2 = mlx_new_image(data.mlx, MNMAP_TILE_S, MNMAP_TILE_S);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    ft_memset(data.map->mnmap_img->pixels, 250, data.map->mnmap_img->width * data.map->mnmap_img->height * sizeof(int32_t));
    // ft_memset(img2->pixels, 196, img2->width * img2->height * sizeof(int32_t));

    mlx_image_to_window(data.mlx, data.map->mnmap_img, 0, 0);
    // mlx_image_to_window(data.mlx, img2, 0, 0);
	// mlx_put_pixel()
	// ab_minimap(&data);
	// for (int i = 0; data.map->map[i]; i++)
	// 	printf("%s\n", data.map->map[i]);
	// printf("\n\n");
	mlx_key_hook(data.mlx, &ab_keyhook, &data); 
	mlx_loop_hook(data.mlx, &ab_minimap, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
