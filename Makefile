# Nom des exécutables
NAME = minishell

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -Ilibft

# Librairies
LIBFT = ./libft/libft.a
LIB = -Llibft -lft

# Fichiers sources
SRC_EXEC = src/exec/src/
FILES_EXEC = exec path copy_env \
			utils identification builtin1 \
			builtin2 free len \
			new_var unset get \
			pipe

SRC_LEXER = src/lexer/src/
FILES_LEXER = 	parser_free parser_utils parser \
				token_utils token \

SRC_DIR	= src/
FILES = 	main_v0 \
			#execution_interface \

SRC_FILES += $(addprefix $(SRC_EXEC), $(FILES_EXEC))
SRC_FILES += $(addprefix $(SRC_LEXER), $(FILES_LEXER))
SRC_FILES += $(addprefix $(SRC_DIR), $(FILES))

SRCS = $(addsuffix .c, $(SRC_FILES))

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF = .cache_exists

# Dépendances
all: $(LIBFT) $(OBJF) $(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJF)
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJF):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIB)
	@echo "\033[32m                                             \033[0m" 
	@echo "\033[32m     __  ____       _      __         ____	\033[0m" 
	@echo "\033[32m    /  |/  (_)___  (_)____/ /_  ___  / / /	\033[0m" 
	@echo "\033[32m   / /|_/ / / __ \/ / ___/ __ \/ _ \/ / / 	\033[0m" 
	@echo "\033[32m  / /  / / / / / / (__  ) / / /  __/ / / 	\033[0m"
	@echo "\033[32m /_/  /_/_/_/ /_/_/____/_/ /_/\___/_/_/   	\033[0m" 
	@echo "\033[32m Minishell compiled successfully!\033[0m"                                                

$(LIBFT):
	@echo " [ .. ] | Compiling libft.."
	make -C libft
	@echo " [ OK ] | Libft ready!"

clean:
	make $@ -C libft
	@rm -rf $(OBJ_DIR)
	@echo "\033[33m Object files and directories removed!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m  Executable removed!\033[0m"

re: fclean all

.PHONY: all clean fclean re