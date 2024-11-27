#include "../main/cub3d.h"


void	ft_load_texture(t_data *data)
{
	data->north_texture = mlx_load_png("images/textures/north200.png");
	if (!data->north_texture)
	{
		printf("Failed to load north texture\n");
		exit(1);
	}
	data->south_texture = mlx_load_png("images/textures/south200.png");
	if (!data->south_texture)
	{
		printf("Failed to load south texture\n");
		exit(1);
	}
	data->east_texture  = mlx_load_png("images/textures/east200.png");
	if (!data->east_texture)
	{
		printf("Failed to load east texture\n");
		exit(1);
	}
	data->west_texture  = mlx_load_png("images/textures/west200.png");
	if (!data->west_texture)
	{
		printf("Failed to load west texture\n");
		exit(1);
	}
	data->door_texture = mlx_load_png("images/textures/door.png");
	if (!data->door_texture)
	{
		printf("Failed to load west texture\n");
		exit(1);
	}
}

void ft_drw_fc(t_data *data)
{
	int	y;
	int	color_floor = get_rgba(169, 169, 169, 255);
	int	color_ceiling = get_rgba(135, 206, 235, 255);


	// Draw the ceiling (upper half of the screen)
	for (y = 0; y < WIN_H / 2; y++) {
		for (int x = 0; x < WIN_W; x++) {
			mlx_put_pixel(data->win_img, x, y, color_ceiling);
		}
	}

	// Draw the floor (lower half of the screen)
	for (y = WIN_H / 2; y < WIN_H; y++) {
		for (int x = 0; x < WIN_W; x++) {
			mlx_put_pixel(data->win_img, x, y, color_floor);
		}
	}
}

void	ft_drctn_bsd_txtr(t_data *data, int i)
{
	if (data->rays[i].door)
		data->applied_texture = data->door_texture;
	else if (data->rays[i].orn == 'h')
	{
		if (data->rays[i].is_up)
			data->applied_texture = data->north_texture;
		else
			data->applied_texture = data->south_texture;
	}
	else
	{
		if (data->rays[i].is_left)
			data->applied_texture = data->west_texture;
		else
			data->applied_texture = data->east_texture;
	}
}


void	ft_clearcolorbuffer(t_data *data, uint32_t color)
{
	int	x;
	int	y;

	(void)color;
	x = 0;
	while (x < TXTR_W)
	{
		y = 0;
		while (y < TXTR_H)
		{
			if (x % 8 && y % 8)
				mlx_put_pixel(data->colorBufferTexture, x, y, get_rgba(0, 0, 0, 255));
			else
				mlx_put_pixel(data->colorBufferTexture, x, y, get_rgba(0, 0, 180, 255));
			y++;
		}
		x++;
	}
}
