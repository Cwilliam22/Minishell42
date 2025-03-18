# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:49:11 by wcapt             #+#    #+#              #
#    Updated: 2025/03/18 16:03:00 by wcapt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom des exécutables
NAME = exec

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Dossiers
SRC_DIR	= src
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Fichiers sources
SRC = 	$(SRC_DIR)/main.c $(SRC_DIR)/path.c $(SRC_DIR)/copy_env.c $(SRC_DIR)/utils.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Dépendances
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[32m exec compiled successfully!\033[0m"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[33m Object files removed!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[31m  Executable removed!\033[0m"

re: fclean all