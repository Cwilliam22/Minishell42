# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfavre <alfavre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 10:55:02 by alfavre           #+#    #+#              #
#    Updated: 2025/02/03 09:40:03 by alfavre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#############################################################################
#								Variables									#
#############################################################################

NAME = libft.a
SRCS_DIR = src/
OBJS_DIR = obj/
CFLAGS = -g -Wall -Wextra -Werror -I include

#############################################################################
#									Sources									#
#############################################################################

FTIS_DIR	=	ft_is/
FTIS		=	ft_isalpha ft_isdigit ft_isalnum ft_isascii \
				ft_isprint

FTMEM_DIR	=	ft_mem/
FTMEM		=	ft_memset ft_memcpy ft_memmove ft_memchr \
				ft_memcmp ft_bzero ft_calloc

FTPUT_DIR	=	ft_put/
FTPUT		=	ft_putchar_fd ft_putstr_fd ft_putendl_fd \
				ft_putnbr_fd

FTTO_DIR	=	ft_to/
FTTO		=	ft_toupper ft_tolower ft_itoa ft_atoi

FTSTR_DIR	=	ft_str/
FTSTR		=	ft_strlen ft_strlcpy ft_strlcat ft_strchr \
				ft_strrchr ft_strncmp ft_strnstr ft_strdup \
				ft_substr ft_strjoin ft_strtrim ft_split \
				ft_strmapi ft_striteri

FTLST_DIR	=	ft_lst/
FTLST		=	ft_lstnew ft_lstadd_front \
				ft_lstsize ft_lstlast \
				ft_lstadd_back ft_lstdelone \
				ft_lstclear ft_lstiter \
				ft_lstmap

FTPRINTF_DIR=	ft_printf/
FTPRINTF	=	ft_printf ft_printf_hexa ft_printf_number \
				ft_printf_word

FTGNL_DIR	=	get_next_line/
FTGNL		=	get_next_line

SRC_FILES += $(addprefix $(FTIS_DIR), $(FTIS))
SRC_FILES += $(addprefix $(FTMEM_DIR), $(FTMEM))
SRC_FILES += $(addprefix $(FTPUT_DIR), $(FTPUT))
SRC_FILES += $(addprefix $(FTTO_DIR), $(FTTO))
SRC_FILES += $(addprefix $(FTSTR_DIR), $(FTSTR))
SRC_FILES += $(addprefix $(FTLST_DIR), $(FTLST))
SRC_FILES += $(addprefix $(FTPRINTF_DIR), $(FTPRINTF))
SRC_FILES += $(addprefix $(FTGNL_DIR), $(FTGNL))

SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

#############################################################################
#									Rules									#
#############################################################################

OBJSF = .cache_exists

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	@echo "Libft compiled!"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJSF)
	@echo "Compiling: $<"
	cc $(CFLAGS) -c $< -o $@

$(OBJSF):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)$(FTIS_DIR)
	mkdir -p $(OBJS_DIR)$(FTMEM_DIR)
	mkdir -p $(OBJS_DIR)$(FTPUT_DIR)
	mkdir -p $(OBJS_DIR)$(FTTO_DIR)
	mkdir -p $(OBJS_DIR)$(FTSTR_DIR)
	mkdir -p $(OBJS_DIR)$(FTLST_DIR)
	mkdir -p $(OBJS_DIR)$(FTPRINTF_DIR)
	mkdir -p $(OBJS_DIR)$(FTGNL_DIR)

clean:
	rm -rf $(OBJS_DIR)
	rm -f $(OBJSF)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
