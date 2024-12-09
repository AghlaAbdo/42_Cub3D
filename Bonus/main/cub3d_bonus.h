/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:12:46 by srachidi          #+#    #+#             */
/*   Updated: 2024/12/08 14:57:48 by aaghla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include "../../mlx42/include/MLX42/MLX42.h"
# include "../../Libft/libft.h"

// Made by Aghla
# define WIN_W 1200
# define WIN_H 675
# define MNMAP_TILE_S 200
# define TXTR_W 200
# define TXTR_H 200
# define MNMAP_W 240
# define MNMAP_H 240
# define MNMAP_GAP 16
# define BIGMAP_W 960
# define BIGMAP_H 576
# define MOVE_SPD 13
# define ROT_SPD 0.03490658504
# define FOV 0.9599310886
# define N_RAYS WIN_W
# define FRM_DUR 60
# define TRN_ON_FRMS 14
# define TRN_OFF_FRMS 17
# define IDLE_ON_FRMS 7
# define WALK_ON_FRMS 9
# define WALK_OFF_FRMS 14

typedef struct s_maplst
{
	char	*line;
	void	*next;
	void	*prev;
}	t_maplst;

typedef struct s_animation
{
	mlx_texture_t	**txtrs;
	// mlx_image_t	**frames;
	mlx_image_t		*frame;
	int				curr_frm;
	double			last_frm_time;
}	t_animation;

typedef struct s_map
{
	char			*no_txt;
	char			*so_txt;
	char			*we_txt;
	char			*ea_txt;
	int				f[3];
	int				c[3];
	t_maplst		*maplst;
	mlx_image_t		*mnmap_img;
	mlx_texture_t	*border_txt;
	mlx_image_t		*border_img;
	mlx_texture_t	*cross_txt;
	mlx_image_t		*cross_img;
	char			**map;
	int				plr_nb;
	int				row;
	int				col;
	double			y;
	double			x;
	double			bigmap_y;
	double			bigmap_x;
	double			bigmap_py;
	double			bigmap_px;
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
	bool	door_h;
	bool	door_v;
	bool	door;
	double	dstn;
	double	real_dstn;	
}	t_rays;

typedef struct s_ln
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
}	t_ln;

typedef struct s_data
{
	mlx_t				*mlx;
	t_map				*map;
	t_player			*plr;
	t_rays				rays[N_RAYS];
	mlx_image_t			*win_img;
	mlx_image_t			*bigmap_img;
	mlx_win_cursor_t	*hnd_cursr;
	bool				is_moving;
	bool				rendering;
	bool				bigmap;
	bool				light;
	bool				mouse;
	int					ms_x;	
	// mlx_texture_t	*cross_txtr;
	// mlx_image_t		*cross_icon;
	mlx_image_t			*shade_bg;
	mlx_image_t			*lighter_on;
	mlx_image_t			*lighter_off;
	t_animation			trn_on_anm;
	t_animation			trn_off_anm;
	t_animation			idle_light_on_anm;
	t_animation			walk_light_on_anm;
	t_animation			walk_light_off_anm;
	// t_mp_txtrs		map_txtrs;
	mlx_image_t			*black_bg;
	bool				turning_on;
	bool				turning_off;
	bool				idle_on;
	bool				walking_on;
	bool				walking_off;
	mlx_image_t			*clrbfrtxtr;
	mlx_texture_t		*north_texture;
	mlx_texture_t		*south_texture;
	mlx_texture_t		*east_texture;
	mlx_texture_t		*west_texture;
	mlx_texture_t		*applied_texture;
	mlx_texture_t		*door_texture;
	int					ln_x1;
	int					ln_y1;
	int					ln_x2;
	int					ln_y2;
	struct s_ln			ln;
	u_int8_t			*rw_pxl;
	int					rw_clr;
	int					rw_alp;
	int					rw_strt_y;
	int					rw_end_y;
	int					rw_y;
	int					rw_dst_frm_tp;
}				t_data;

typedef modifier_key_t	t_mdf_ky;

void		ft_load_texture(t_data *data);
void		ft_drw_fc(t_data *data);
void		ft_drctn_bsd_txtr(t_data *data, int i);
void		ft_clearcolorbuffer(t_data *data, uint32_t color);
int			get_texture_x(t_data *data, t_rays *ray, int texture_width);
void		sr_id_check(t_data *data, char *line, int strt, char *id);
void		sr_remover(t_data *data, char *id);
int			sr_is_vld(char *str);
void		*ft_malloc(size_t size, int mode);
int			parse_file(t_data *data, char *file);
int			first_part(t_data *data, char *line);
int			sec_part(t_data *data, t_maplst **maplst, char *line);
int			sr_len(char *s);
char		*sr_dup(char *s);
char		*sr_substr(char *s, int start, int len);
int			sr_strcmp( char *s1, char *s2);
void		sr_rmv_nline(char *str);
// void		ft_megamind(t_data data);
void		init_data_nrm(t_data *data);
// void		ab_fill_line(char *dst, char *src, int len);

//	Made by Aghla
t_maplst	*ab_maplst_new(char *line);
void		ab_maplstaddb(t_maplst **lst, t_maplst *new);
int			ab_maplst_size(t_maplst *lst);
void		ab_valid_map(t_data *data, t_maplst *maplst);
void		ft_looper(void *param);
void		move_plr(t_data *data);
void		handle_mouse(t_data *data);
bool		is_plr_moving(t_data *data);
void		draw_mnmap(t_data *data, int x, int y);
void		draw_mnmap_rays(t_data *data);
void		draw_bigmap(t_data *data);
void		clean_exit_pars(t_data *data, char *err, int stat);
void		ab_ft_drw_ln(t_data *data, int color);
void		draw_circle(mlx_image_t *img, int h, int k, int r);
// void		draw_ray(t_data *data, int x, int y, int w, int h);
int			get_rgba(int r, int g, int b, int a);
void		raycasting(t_data *data);
int			check_wall(t_data *data, int p_x, int p_y);
void		mse_evnt(mouse_key_t btn, action_t actn,
				modifier_key_t mds, void *prm);
void		check_mouse_pos(t_data *data);
// void		draw_shade_bg(t_data *data);
void		clean_exit(t_data *data, char *err, int stat);
// void	delete_wall_txtrs(t_data *data);
void		init_data(t_data *data);
void		ab_set_orn(t_data *data);
t_data		*get_data(t_data *curr_data);
void		check_plr_exist(t_data *data, char **map);

//	Raycasting
void		calc_horz(t_data *data, t_rays *ray, double xstep, int up);
void		calc_vert(t_data *data, t_rays *ray, double xstep, int left);
void		ab_set_rayangl(t_data *data);
void		cmp_vh_dst(t_data *data, t_rays *ray, double h_dstn, double v_dstn);
void		calc_dstn(t_data *data, t_rays *ray, double h_dstn, double v_dstn);
double		adjust_angle(double angle);
void		set_alpha(t_data *data, t_rays ray, int *alpha);
void		renderworld(t_data *data);
//	Animation
void		anm_turn_light_on(t_data *data, t_animation *anm, double curr_time);
void		anm_idle_light_on(t_data *data, t_animation *anm, double curr_time);
void		anm_turn_light_off(t_data *data, t_animation *anm, double crr_tm);
void		anm_walk_light_on(t_data *data, t_animation *anm, double curr_time);
void		anm_walk_light_off(t_data *data, t_animation *anm, double crr_tm);
void		safe_delete_img(t_data *data, mlx_image_t **img);

//	Events
void		handle_events(mlx_key_data_t keydata, void *param);
void		show_big_map(t_data *data);
void		hide_big_map(t_data *data);
void		switch_light(t_data *data);
void		close_hook(void	*param);

//	Init images
void		init_images(t_data *data);
void		init_turning_on_imgs(t_data *data, t_animation *anm);
void		init_idle_light_on_imgs(t_data *data, t_animation *anm);
void		init_turning_off_imgs(t_data *data, t_animation *anm);
void		init_walking_on_imgs(t_data *data, t_animation *anm);
void		init_walking_off_imgs(t_data *data, t_animation *anm);

#endif