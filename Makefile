# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/14 17:53:07 by mouaammo          #+#    #+#              #
#    Updated: 2022/12/20 18:03:40 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft
NAME = pipex
RM = rm -rf
SRC = pipex utils count_words help_split split_proc
SRC_BONUS = pipex_bonus utils_bonus utils count_words help_split split_proc
OBJ = $(SRC:=.o)
OBJ_BONUS = $(SRC_BONUS:=.o)
GET_LINE = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
LFT = ./libft/libft.a


all : $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFT) -o $(NAME)

bonus: $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LFT) $(GET_LINE) -o $(NAME)

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)
	@echo "--- Object files are Cleand."

fclean: clean
	@$(RM) $(NAME)
	@echo "--- ALL Cleand."

re: fclean all
.PHONY: all fclean clean re bonus
