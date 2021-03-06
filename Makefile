# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/16 19:30:49 by jtaylor           #+#    #+#              #
#    Updated: 2020/01/15 17:13:49 by jtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = jtaylor.filler

FLAGS = -Wall -Wextra -Werror -I ./libft/includes

OPT_FLAGS = -Ofast
FLAGS += $(OPT_FLAGS)

DEBUG_FLAG = -g3

FSANITIZE = -fsanitize=address -fsanitize=undefined

LINKED_LIB =

FRAMEWORK =


INCLUDES = -I ./libft/includes
INCLUDES += -I ./includes

SRC_FILE =	main.c \
			map_parsing/parse.c \
			map_parsing/map_specific_parsing.c \
			map_parsing/update_map_and_piece.c \
			map_parsing/input_map_to_int_matrix.c \
			cleanup/free_struct.c \
			alg/check_valid_piece.c \
			alg/find_placement.c \
			alg/chose_dir_to_fill_in.c \
			alg/y_prio.c \
			alg/x_prio.c

SRC = $(addprefix ./src/, $(SRC_FILE))

.PHONY = all clean fclean re

all : $(NAME)

$(NAME) :
	@make -C ./libft
	@echo "\tBuilding $(NAME) executable\n"
	gcc $(FLAGS) $(INCLUDES) $(SRC) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

debug :
	@make debug -C ./libft
	@echo "\tBuilding $(NAME) debug executable\n"
	gcc $(FLAGS) $(DEBUG_FLAG) $(INCLUDES) $(SRC) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)

fsan :
	@make -C ./libft
	@echo "\tBuilding $(NAME) executable\n"
	gcc $(DEBUG_FLAG) $(FSANITIZE) $(SRC) $(INCLUDES) ./libft/libft.a ./libft/ft_printf/libftprintf.a -o $(NAME)


clean :
	@make -C libft clean

fclean : clean
	@echo "\tRemoving $(NAME) Executable\n"
	@rm -rf $(NAME)
	@rm -rf $(NAME).dSYM
	@make -C libft fclean

re : fclean all

r :
	rm $(NAME);
	make all
