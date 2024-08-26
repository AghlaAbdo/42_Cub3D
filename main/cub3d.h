/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:12:46 by srachidi          #+#    #+#             */
/*   Updated: 2024/08/26 17:43:11 by aaghla           ###   ########.fr       */
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
# include "../MLX/include/MLX42/MLX42.h"
// # include "MLX/include/MLX42/MLX42_Int.h"
# include "../get_next_line/get_next_line.h"
# include "../Libft/libft.h"

// Made by Aghla
# define MNMAP_TILE_S 32
# define MNMAP_W (MNMAP_TILE_S * 8)
# define MNMAP_H (MNMAP_TILE_S * 6)
# define MOVE_SPD 4
# define ROT_SPD 8 * (M_PI / 180)


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
	char		**map;
	int			plr_nb;
	int			row;
	int			col;
}				t_map;

typedef struct s_player
{
	int	y;
	int	x;
	double	rot_angl;
}	t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	*plr;
	
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
void		clean_exit(char *err, int stat);

#endif