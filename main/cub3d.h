/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:12:46 by srachidi          #+#    #+#             */
/*   Updated: 2024/09/08 08:59:14 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include "../MLX/include/MLX42/MLX42.h"
# include "../Libft/libft.h"

// Made by Aghla
# define WIN_W 1200
# define WIN_H 675
# define MNMAP_TILE_S 24
# define MNMAP_W (MNMAP_TILE_S * 10)
# define MNMAP_H (MNMAP_TILE_S * 10)
# define MNMAP_GAP 16
# define BIG_MNMAP_W 960
# define BIG_MNMAP_H 576
# define MOVE_SPD 1.3
# define ROT_SPD 2 * (M_PI / 180)
# define FOV 60 * (M_PI / 180)
# define N_RAYS (WIN_W)

typedef struct s_addr
{
	void	*addr;
	void	*next;
}	t_addr;

typedef struct s_maplst
{
	char	*line;
	void	*next;
	void	*prev;
}	t_maplst;

typedef struct s_map
{
	char		*no_txt;
	char		*so_txt;
	char		*we_txt;
	char		*ea_txt;
	int			f[3];
	int			c[3];

	t_maplst	*maplst;
	mlx_image_t	*mnmap_img;
	mlx_texture_t	*border_txtr;
	mlx_image_t	*border;
	char		**map;
	int			plr_nb;
	int			row;
	int			col;
	double		y;
	double		x;
	double		p_y;
	double		p_x;
}				t_map;

typedef struct s_player
{
	double	y;
	double	x;
	char	orn;
	double	rot_angl;
}	t_player;

// angl: ray angle
// yinter: y intercept
// xinter: x intercept
// dstn: ray distance;
// is_left: is ray facing left
// is_up: is ray facing up0
typedef struct s_rays
{
	double	angl;
	double	x;
	double	y;
	double	h_x;
	double	h_y;
	double	v_x;
	double	v_y;
	char	orn;
	bool	found_h;
	bool	found_v;
	bool	is_left;
	bool	is_up;
	double	dstn;
	double	real_dstn;
	
}	t_rays;

typedef struct s_data
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	*plr;
	t_rays		rays[N_RAYS];
	mlx_image_t	*win_img;
	mlx_image_t	*big_mnmp_img;
	mlx_win_cursor_t	*hnd_cursr;
	bool		is_moving;
	bool		big_mnmap;
	bool		light;
	bool		mouse;
	int			ms_x;
	
	mlx_texture_t	*cross_txtr;
	mlx_image_t		*cross_icon;
	mlx_image_t		*shade_bg;
	
}				t_data;


void	*ft_malloc(size_t size, int mode);
int		parse_file(t_data *data, char *file);
int		first_part(t_data *data, char *line);
int		sec_part(t_data *data, t_maplst **maplst, char *line);

//	Made by Aghla
t_maplst	*ab_maplst_new(char *line);
void 		ab_maplstaddb(t_maplst **lst, t_maplst *new);
int			ab_maplst_size(t_maplst *lst);
void		ab_valid_map(t_data *data, t_maplst *maplst);
void		ft_looper(void *param);
void		plr_move(t_data *data);
void		handle_mouse(t_data *data);
bool		ab_is_moving(t_data *data);
void		draw_mnmap(t_data *data);
void		draw_mnmap_rays(t_data *data);
void		draw_big_mnmap(t_data *data);
void		clean_exit(char *err, int stat);
void		ab_drawline(t_data *data, int x1, int y1, int x2, int y2, int color);
void		draw_circle(mlx_image_t *img, int h, int k, int r);
void		draw_ray(t_data *data, int x, int y, int w, int h);
int			get_rgba(int r, int g, int b, int a);
void		raycasting(t_data *data);
int			check_wall(t_data *data, int p_x, int p_y);
void		mouse_event(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void		check_mouse_pos(t_data *data);

#endif