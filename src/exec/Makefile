# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: william <william@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:49:11 by wcapt             #+#    #+#              #
#    Updated: 2025/03/31 15:20:10 by william          ###   ########.fr        #
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
SRC = 	$(SRC_DIR)/main.c $(SRC_DIR)/path.c $(SRC_DIR)/copy_env.c \
		$(SRC_DIR)/utils.c $(SRC_DIR)/identification.c $(SRC_DIR)/builtin1.c \
		$(SRC_DIR)/builtin2.c 

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Dépendances
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[32m  _______      ___    ___ _______   ________     \033[0m" 
	@echo "\033[32m |\  ___ \    |\  \  /  /|\  ___ \ |\   ____\    \033[0m"
	@echo "\033[32m \ \   __/|   \ \  \/  / | \   __/|\ \  \___|    \033[0m"
	@echo "\033[32m  \ \  \_|/__  \ \    / / \ \  \_|/_\ \  \       \033[0m"
	@echo "\033[32m   \ \  \_|\ \  /     \/   \ \  \_|\ \ \  \____  \033[0m"
	@echo "\033[32m    \ \_______\/  /\   \    \ \_______\ \_______\\033[0m"
	@echo "\033[32m     \|_______/__/ /\ __\    \|_______|\|_______|\033[0m"
	@echo "\033[32m              |__|/ \|__|                        \033[0m"
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