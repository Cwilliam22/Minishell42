# Nom des exécutables
NAME = minishell

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Dossiers
SRC_DIR	= src

# Fichiers sources
SRC = 	$(SRC_DIR)/main.c

OBJ = $(SRC:.c=.o)

# Dépendances
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
	@echo "\033[32m                                             \033[0m" 
	@echo "\033[32m     __  ____       _      __         ____	\033[0m" 
	@echo "\033[32m    /  |/  (_)___  (_)____/ /_  ___  / / /	\033[0m" 
	@echo "\033[32m   / /|_/ / / __ \/ / ___/ __ \/ _ \/ / / 	\033[0m" 
	@echo "\033[32m  / /  / / / / / / (__  ) / / /  __/ / / 	\033[0m"
	@echo "\033[32m /_/  /_/_/_/ /_/_/____/_/ /_/\___/_/_/   	\033[0m" 
	@echo "\033[32m Minishell compiled successfully!\033[0m"                                                

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[33m Object files removed!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m  Executable removed!\033[0m"

re: fclean all