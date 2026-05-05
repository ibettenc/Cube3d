# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 19:36:14 by ibettenc          #+#    #+#              #
#    Updated: 2026/05/05 15:30:33 by ibettenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################################
## ARGUMENTS

NAME = cub3d

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Iincludes -Iincludes/mlx -g

MLX_FLAGS = -Lincludes/mlx -lmlx -lXext -lX11 -lm

LIBFT = includes/libft/libft.a


###################################################
## SOURCES

SRC_DIR = srcs

OBJ_DIR = obj

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/mlx_init.c \
      $(SRC_DIR)/hooks.c \
      $(SRC_DIR)/render.c \
	  $(SRC_DIR)/player.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

###################################################
## RULES

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

##################################################
## CLEAN

clean:
		@rm -f $(OBJ)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all  clean fclean re
