# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibettenc <ibettenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 13:43:25 by ibettenc          #+#    #+#              #
#    Updated: 2025/11/07 12:12:35 by ibettenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## ARGUMENTS

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

CC = gcc

###################################################
## SOURCES

SRC = ft_strlen.c ft_strdup.c ft_strchr.c ft_strncmp.c ft_atoi.c ft_strrchr.c \
       ft_strjoin.c ft_split.c ft_print_utils.c ft_printf.c ft_itoa.c \
       get_next_line.c get_next_line_utils.c ft_memset.c ft_strlcpy.c

SRCB = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
	ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_print_utils.c ft_printf.c

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

###################################################
## RULES

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
##################################################
## POUR TESTER
#
#so:
#	$(CC) -fPIC $(CFLAGS) $(SRC) $(SRCB)
#	gcc -shared -o libft.so $(OBJ) $(OBJB)
#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC) $(SRCB)
#	gcc -nostartfiles -shared -o libft.so $(OBJ) $(OBJB)
##################################################
## BONUS

bonus: $(OBJ) $(OBJB)
	ar rcs $(NAME) $(OBJ) $(OBJB)

##################################################
## CLEAN

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
