# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 14:07:31 by alfavre           #+#    #+#              #
#    Updated: 2025/04/23 15:38:30 by alfavre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################################################
#								Variables									#
#############################################################################
NAME = lexer
LIBFT = ./libft/libft.a
SRC_DIR = src/
OBJ_DIR = obj/
INC = -I/home/alfavre/Documents/42_github/Minishell42/include -Ilibft
LIB = -Llibft -lft
CC = gcc
FLAGS = -g -Wall -Wextra -Werror

#############################################################################
#									Sources									#
#############################################################################
SRC_FILES = debug test\
			parser_free parser_utils parser \
			token_utils token

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