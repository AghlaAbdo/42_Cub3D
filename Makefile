# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thedon <thedon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 06:34:23 by srachidi          #+#    #+#              #
#    Updated: 2025/04/06 12:14:26 by thedon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
NAME_BNS	= cub3D_bonus
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
O_DR	= objs/
LIBFT	= Libft/libft.a
MLX		= mlx42/build/libmlx42.a
SRC		:=	Mandatory/main/main.c						\
			Mandatory/main/loop.c						\
			Mandatory/main/big_minimap.c				\
			Mandatory/main/movement.c					\
			Mandatory/main/events.c					\
			Mandatory/main/init_data.c				\
			Mandatory/main/init_images.c				\
			Mandatory/main/move_player.c				\
			Mandatory/main/clean_exit.c					\
			Mandatory/parsing/parse_file.c				\
			Mandatory/parsing/fst_part.c				\
			Mandatory/parsing/fst_part1.c				\
			Mandatory/parsing/sec_part.c				\
			Mandatory/parsing/sec_part1.c				\
			Mandatory/parsing/ab_map_lst.c				\
			Mandatory/raycasting/raycasting.c			\
			Mandatory/raycasting/raycasting1.c			\
			Mandatory/raycasting/calc_dstn.c			\
			Mandatory/raycasting/renderworld.c			\
			Mandatory/parsing/sr_tools/sr_tools1.c		\
			Mandatory/raycasting/textures.c 			\
			Mandatory/raycasting/textures1.c

SRC_BNS	:=	Bonus/main/main_bonus.c						\
			Bonus/main/loop_bonus.c						\
			Bonus/main/minimap_bonus.c					\
			Bonus/main/minimap1_bonus.c					\
			Bonus/main/big_minimap_bonus.c				\
			Bonus/main/drawing_bonus.c					\
			Bonus/main/movement_bonus.c					\
			Bonus/main/mouse_events_bonus.c				\
			Bonus/main/animation_bonus.c				\
			Bonus/main/events_bonus.c					\
			Bonus/main/init_data_bonus.c				\
			Bonus/main/init_images_bonus.c				\
			Bonus/main/init_images2_bonus.c				\
			Bonus/main/move_player_bonus.c				\
			Bonus/main/clean_exit_bonus.c				\
			Bonus/parsing/parse_file_bonus.c			\
			Bonus/parsing/fst_part_bonus.c				\
			Bonus/parsing/fst_part1_bonus.c				\
			Bonus/parsing/sec_part_bonus.c				\
			Bonus/parsing/sec_part1_bonus.c				\
			Bonus/parsing/ab_map_lst_bonus.c			\
			Bonus/raycasting/raycasting_bonus.c			\
			Bonus/raycasting/raycasting1_bonus.c		\
			Bonus/raycasting/calc_dstn_bonus.c			\
			Bonus/raycasting/renderworld_bonus.c		\
			Bonus/parsing/sr_tools/sr_tools1_bonus.c	\
			Bonus/raycasting/textures_bonus.c 			\
			Bonus/raycasting/textures1_bonus.c 

CLR_RMV := \033[0m
RED     := \033[1;31m
GREEN   := \033[1;32m
PURPLE  := \033[35m
BLUE    := \033[1;34m
CYAN    := \033[1;36m
OBJ		= $(addprefix $(O_DR),$(SRC:.c=.o))
OBJ_BNS	= $(addprefix $(O_DR),$(SRC_BNS:.c=.o))
MLX_DIR  = ./mlx42/build

all : libft_rule mlx_rule $(NAME)

bonus : libft_rule mlx_rule $(NAME_BNS)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo "$(CYAN)Compilation ${CLR_RMV}of ${PURPLE}$(NAME) ${CLR_RMV}..."
	# For MacOs
	#@$(CC) $(CFLAGS) $^ -o $@ $(MLX) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(LIBFT)
	# For Linux
	@$(CC) $(CFLAGS) $^ -o $@ $(MLX) -lglfw -ldl -lm -lX11 -lpthread -lXrandr -lXi $(LIBFT)

	@echo "$(GREEN)$(NAME) created Successfully${CLR_RMV} ✔️"

$(NAME_BNS) : $(OBJ_BNS) $(LIBFT) $(MLX)
	@echo "$(CYAN)Compilation ${CLR_RMV}of ${PURPLE}$(NAME) ${CLR_RMV}..."
	# For MacOs
	#@$(CC) $(CFLAGS) $^ -o $@ $(MLX) -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(LIBFT)
	# For Linux
	@$(CC) $(CFLAGS) $^ -o $@ $(MLX) -lglfw -ldl -lm -lX11 -lpthread -lXrandr -lXi $(LIBFT)
	@echo "$(GREEN)$(NAME) created Successfully${CLR_RMV} ✔️"

mlx_rule:
	@(cd mlx42 && cmake -B build && cmake --build build -j4)

$(O_DR)%_bonus.o: %_bonus.c Bonus/main/cub3d_bonus.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(O_DR)%.o: %.c Mandatory/main/cub3d.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

libft_rule:
	@make -C Libft

clean :
	@$(RM) $(O_DR)
	@ echo "$(RED)Deleting $(PURPLE)$(NAME) $(CLR_RMV)objs ✔️"
	@make -C Libft clean

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BNS)
	@$(RM) $(MLX_DIR)
	@rm -f $(LIBFT)
	@ echo "$(RED)Deleting $(PURPLE)$(NAME) $(CLR_RMV)binary ✔️"

mc : all clean

re : fclean all

.PHONY : all clean fclean re mc