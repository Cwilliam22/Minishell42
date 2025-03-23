# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 14:07:31 by alfavre           #+#    #+#              #
#    Updated: 2025/03/23 15:34:00 by alfavre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################################################
#								Variables									#
#############################################################################
NAME = lexer
LIBFT = ./libft/libft.a
SRC_DIR = src/
OBJ_DIR = obj/
INC = -Iinclude -Ilibft
LIB = -Llibft -lft -lreadline -lhistory
CC = gcc
FLAGS = -g -Wall -Wextra -Werror

#############################################################################
#									Sources									#
#############################################################################
SRC_FILES = lexer_utils token token_utils op_token

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

#############################################################################
#									Rules									#
#############################################################################
OBJF = .cache_exists

all: $(LIBFT) $(OBJF) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "Compiling $<"
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

$(LIBFT):
	@echo " [ .. ] | Compiling libft.."
	make -C libft
	@echo " [ OK ] | Libft ready!"

$(OBJF):
	mkdir -p $(OBJ_DIR)

clean:
	make $@ -C libft
	rm -rf $(OBJ_DIR)
	@echo "object files removed."

fclean: clean
	make $@ -C libft
	rm -rf $(NAME)
	@echo "binary file removed."

re: fclean all

.PHONY: all clean fclean re