# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghla <aaghla@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 06:34:23 by srachidi          #+#    #+#              #
#    Updated: 2024/09/07 20:21:04 by aaghla           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = cub3D
CC     = cc
CFLAGS = -DDEBUG=1 #-Wall -Wextra -Werror
RM     = rm -rf
O_DR   = objs/
LIBFT	= Libft/libft.a
SRC    := main/grbgcllctr.c			\
			main/main.c				\
			main/loop.c				\
			main/minimap.c			\
			main/big_minimap.c		\
			main/drawing.c			\
			main/movement.c			\
			main/mouse_events.c		\
			parsing/parse_file.c	\
			parsing/fst_part.c		\
			parsing/sec_part.c		\
			parsing/ab_map_lst.c	\
			raycasting/raycasting.c

CLR_RMV := \033[0m
RED     := \033[1;31m
GREEN   := \033[1;32m
PURPLE  := \033[35m
BLUE    := \033[1;34m
CYAN    := \033[1;36m
OBJ    = $(addprefix $(O_DR),$(SRC:.c=.o))

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(CYAN)Compilation ${CLR_RMV}of ${PURPLE}$(NAME) ${CLR_RMV}..."
	@$(CC) $(CFLAGS) $^ -o $@ ./MLX/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(LIBFT)
	@echo "$(GREEN)$(NAME) created Successfully${CLR_RMV} ✔️"

$(LIBFT):
	@echo "$(CYAN)Compiling ${CLR_RMV}${PURPLE}Libft${CLR_RMV}"
	@make -C Libft

$(O_DR)%.o: %.c main/cub3d.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

all : $(NAME)

clean :
	@$(RM) $(O_DR)
	@ echo "$(RED)Deleting $(PURPLE)$(NAME) $(CLR_RMV)objs ✔️"
	@make -C Libft clean

fclean : clean
	@$(RM) $(NAME)
	@rm -f $(LIBFT)
	@ echo "$(RED)Deleting $(PURPLE)$(NAME) $(CLR_RMV)binary ✔️"

mc : all clean

re : fclean all

.PHONY : all clean fclean re mac